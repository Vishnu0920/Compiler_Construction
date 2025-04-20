%{
#include "a.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ASTNode* rootNode = NULL;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

/* Check if a number base is valid (2, 8, or 10) */
int is_valid_base(int base) {
    return (base == 2 || base == 8 || base == 10);
}
%}

%code requires {
    #include "a.h"
}

%union {
    int int_val;
    char* str_val;
    ASTNode* ast;
}

%token BEGIN_K END_K PROGRAM COLON SEMICOLON COMMA LPAR RPAR LBRACK RBRACK
%token INT CHAR PRINT SCAN VARDECL INC DEC
%token ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP
%token <str_val> ID STRING CHARACTER FORMAT_STRING INPUT_STRING
%token <int_val> NUMBER
%token IF_K ELSE_K WHILE_K FOR_K TO_K DO_K
%token EQ NEQ GT LT GEQ LEQ
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token NL

%type <ast> NUM
%type <str_val> VarName VarNameDecl
%type <ast> ArithmeticExpression Primary Factor Term
%type <ast> Program VarDeclSection DeclList Decl StatementSection StatementList
%type <ast> Statement OutputStmt InputStmt Assignment ConditionalStmt LoopStmt
%type <ast> Block Condition AssnArg OutputArg OutputArgList PrintArg InputArgList
%type <int_val> RelOp LoopOp Type
%type <str_val> InputString

%right ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%left ADD_OP SUB_OP
%left MUL_OP DIV_OP MOD_OP
%nonassoc UMINUS
%nonassoc EQ NEQ GT LT GEQ LEQ

%nonassoc IF_PREC
%nonassoc ELSE_K

%define parse.error verbose

%start Program

%%

Program:
    BEGIN_K PROGRAM COLON VarDeclSection StatementSection END_K PROGRAM
    {
        rootNode = createProgramNode($4, $5);
        printf("Successfully parsed program structure\n");
    }
    ;

VarDeclSection:
    BEGIN_K VARDECL COLON DeclList END_K VARDECL
    {
        $$ = $4;
        printf("Successfully parsed variable declaration section\n");
    }
    ;

DeclList:
      Decl DeclList {
          $$ = createDeclListNode($1, $2);
      }
    | /* empty */ {
          $$ = NULL;
      }
    ;

Decl:
    LPAR VarNameDecl COMMA Type RPAR SEMICOLON
    {
        $$ = createVarDeclNode($2, $4);
        printf("Parsed variable declaration: %s\n", $2);
    }
    ;

Type:
      INT { $$ = INT; printf("Type: int\n"); }
    | CHAR { $$ = CHAR; printf("Type: char\n"); }
    ;

VarNameDecl:
      ID                      
    {
        $$ = $1;
        printf("Variable name: %s\n", $1);
    }
    | ID LBRACK NUMBER RBRACK
    {
        $$ = $1;
        printf("Array declaration: %s[%d]\n", $1, $3);
    }
    ;

VarName:
      ID {
        $$ = $1;
      }
    | ID LBRACK ArithmeticExpression RBRACK {
        $$ = $1;
      }
    ;

StatementSection:
      StatementList {
          $$ = $1;
          printf("Successfully parsed statement section\n");
      }
    | /* empty */ { $$ = NULL; }
    ;

StatementList:
      Statement StatementList {
          $$ = createStatementListNode($1, $2);
      }
    | Statement {
          $$ = $1;
      }
    ;

Statement:
      OutputStmt { $$ = $1; }
    | InputStmt { $$ = $1; }
    | Assignment { $$ = $1; }
    | ConditionalStmt { $$ = $1; }
    | LoopStmt { $$ = $1; }
    ;

OutputStmt:
    PRINT LPAR PrintArg RPAR SEMICOLON
    {
        $$ = createPrintNode($3);
        printf("Parsed print statement\n");
    }
    ;

PrintArg:
      STRING { $$ = createStringNode($1); printf("Print string literal\n"); }
    | INPUT_STRING COMMA OutputArgList { $$ = createFormatStringNode($1, $3); printf("Print input format string with arguments\n"); }
    | FORMAT_STRING COMMA OutputArgList { $$ = createFormatStringNode($1, $3); printf("Print format string with arguments\n"); }
    ;

OutputArgList:
      OutputArg { $$ = $1; }
    | OutputArg COMMA OutputArgList { $$ = createOutputArgListNode($1, $3); }
    ;

OutputArg:
      ArithmeticExpression { $$ = $1; }
    | STRING { $$ = createStringNode($1); }
    | CHARACTER { $$ = createCharNode($1); }
    ;

InputStmt:
    SCAN LPAR InputString COMMA InputArgList RPAR SEMICOLON
    {
        $$ = createScanNode($3, $5);
        printf("Parsed scan statement\n");
    }
    ;

InputString:
    INPUT_STRING
    ;

InputArgList:
      VarName { $$ = createVarRefNode($1); printf("Input to variable: %s\n", $1); }
    | VarName COMMA InputArgList { $$ = createInputArgListNode(createVarRefNode($1), $3); printf("Input to variable: %s\n", $1); }
    ;

Assignment:
      VarName ASSIGN AssnArg SEMICOLON
    {
        $$ = createAssignNode($1, $3);
        printf("Parsed assignment with :=\n");
    }
    | VarName ADD_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_ADD_ASSIGN, $1, $3);
        printf("Parsed assignment with +=\n");
    }
    | VarName SUB_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_SUB_ASSIGN, $1, $3);
        printf("Parsed assignment with -=\n");
    }
    | VarName MUL_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_MUL_ASSIGN, $1, $3);
        printf("Parsed assignment with *=\n");
    }
    | VarName DIV_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_DIV_ASSIGN, $1, $3);
        printf("Parsed assignment with /=\n");
    }
    | VarName MOD_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_MOD_ASSIGN, $1, $3);
        printf("Parsed assignment with %%=\n");
    }
    ;

AssnArg:
      STRING { $$ = createStringNode($1); }
    | CHARACTER { $$ = createCharNode($1); }
    | ArithmeticExpression { $$ = $1; }
    ;

NUM:
      LPAR NUMBER COMMA NUMBER RPAR  
    {
        if (!is_valid_base($4)) {
            fprintf(stderr, "Semantic Error: Invalid number base %d. Only bases 2, 8, and 10 are allowed.\n", $4);
            YYABORT;
        }
        $$ = createNumberNode($2, $4);
        printf("Number: %d in base %d\n", $2, $4);
    }
    | NUMBER
    {
        $$ = createNumberNode($1, 10);  // Default base 10
        printf("Number: %d in base 10\n", $1);
    }
    ;


ConditionalStmt:
      IF_K LPAR Condition RPAR Block SEMICOLON %prec IF_PREC
    {
        $$ = createIfNode($3, $5, NULL);
        printf("Parsed if statement\n");
    }
    | IF_K LPAR Condition RPAR Block ELSE_K Block SEMICOLON
    {
        $$ = createIfNode($3, $5, $7);
        printf("Parsed if-else statement\n");
    }
    ;

Block:
    BEGIN_K StatementList END_K
    {
        $$ = createBlockNode($2);
        printf("Parsed block of statements\n");
    }
    ;

LoopStmt:
      WHILE_K LPAR Condition RPAR DO_K BEGIN_K StatementList END_K SEMICOLON
    {
        $$ = createWhileNode($3, createBlockNode($7));
        printf("Parsed while loop\n");
    }
    | FOR_K VarName ASSIGN ArithmeticExpression TO_K ArithmeticExpression LoopOp ArithmeticExpression DO_K BEGIN_K StatementList END_K SEMICOLON
    {
        $$ = createForNode(createVarRefNode($2), $4, $6, $7, $8, $11);
        printf("Parsed for loop\n");
    }
    ;

LoopOp:
      INC { $$ = INC; printf("Loop operator: inc\n"); }
    | DEC { $$ = DEC; printf("Loop operator: dec\n"); }
    ;

Condition:
      ArithmeticExpression RelOp ArithmeticExpression
    {
        NodeType opType;
        switch ($2) {
            case EQ: opType = NODE_EQ; break;
            case NEQ: opType = NODE_NEQ; break;
            case GT: opType = NODE_GT; break;
            case LT: opType = NODE_LT; break;
            case GEQ: opType = NODE_GEQ; break;
            case LEQ: opType = NODE_LEQ; break;
            default: opType = NODE_EQ; // Default
        }
        $$ = createOperatorNode(opType, $1, $3);
        printf("Parsed condition\n");
    }
    ;

RelOp:
      EQ  { $$ = EQ; printf("Relational operator: =\n"); }
    | NEQ { $$ = NEQ; printf("Relational operator: <>\n"); }
    | GT  { $$ = GT; printf("Relational operator: >\n"); }
    | LT  { $$ = LT; printf("Relational operator: <\n"); }
    | GEQ { $$ = GEQ; printf("Relational operator: >=\n"); }
    | LEQ { $$ = LEQ; printf("Relational operator: <=\n"); }
    ;

ArithmeticExpression:
      Term                                    { $$ = $1; }
    | ArithmeticExpression ADD_OP Term        {
        $$ = createOperatorNode(NODE_ADD, $1, $3);
        printf("Addition\n");
    }
    | ArithmeticExpression SUB_OP Term        {
        $$ = createOperatorNode(NODE_SUB, $1, $3);
        printf("Subtraction\n");
    }
    ;

Term:
      Factor                           { $$ = $1; }
    | Term MUL_OP Factor               {
        $$ = createOperatorNode(NODE_MUL, $1, $3);
        printf("Multiplication\n");
    }
    | Term DIV_OP Factor               {
        $$ = createOperatorNode(NODE_DIV, $1, $3);
        printf("Division\n");
    }
    | Term MOD_OP Factor               {
        $$ = createOperatorNode(NODE_MOD, $1, $3);
        printf("Modulo\n");
    }
    ;

Factor:
      Primary                          { $$ = $1; }
    | SUB_OP Factor %prec UMINUS       {
        $$ = createOperatorNode(NODE_NEG, createNumberNode(0,10), $2);
        printf("Unary minus\n");
    }
    ;

Primary:
      NUM                              { $$ = $1; }
    | VarName                          {
        $$ = createVarRefNode($1);
    }
    | LPAR ArithmeticExpression RPAR   {
        $$ = $2;
        printf("Parenthesized expression\n");
    }
    ;


%%

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }
   
    int result = yyparse();
   
    if (result == 0 && rootNode != NULL) {
        printf("\nGenerated AST:\n");
        printAST(rootNode, 0);
        printf("\n");
        freeAST(rootNode);
    }
   
    return result;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s\n", s);
}


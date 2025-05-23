%{
#include "a.h"
#include "a.tab.h" 
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

/* Check if a number's digits are valid for the given base */
int is_valid_number_for_base(int num, int base) {
    // Handle negative numbers by checking absolute value
    int absNum = (num < 0) ? -num : num;
    
    // Special case for 0
    if (absNum == 0) return 1;
    
    while (absNum > 0) {
        int digit = absNum % 10;
        if (digit >= base) return 0;  // Invalid digit for this base
        absNum /= 10;
    }
    return 1;  // All digits are valid
}

int countPlaceholders(const char* fmt) {
    int count = 0;
    for (const char* p = fmt; *p; p++) {
        if (*p == '@') count++;
    }
    return count;
}

int countArgs(ASTNode* node) {
    if (!node) return 0;
    return 1 + countArgs(node->data.op.right);
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
    }
    ;

VarDeclSection:
    BEGIN_K VARDECL COLON DeclList END_K VARDECL
    {
        $$ = $4;
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
    }
    ;

Type:
      INT { $$ = INT; }
    | CHAR { $$ = CHAR; }
    ;

VarNameDecl:
      ID                      
    {
        $$ = $1;
    }
    | ID LBRACK NUMBER RBRACK
    {
        $$ = $1;
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
    }
    ;

PrintArg:
      STRING { $$ = createStringNode($1); }
    | INPUT_STRING COMMA OutputArgList {
        int expectedArgs = countPlaceholders($1);
        int actualArgs = countArgs($3);

        if (expectedArgs != actualArgs) {
            fprintf(stderr, "Error: Mismatched argument count in print statement. Expected %d, got %d.\n", expectedArgs, actualArgs);
            YYABORT;
        }
        
        $$ = createFormatStringNode($1, $3); 
    }
    | FORMAT_STRING COMMA OutputArgList {
        int expectedArgs = countPlaceholders($1);
        int actualArgs = countArgs($3);

        if (expectedArgs != actualArgs) {
            fprintf(stderr, "Error: Mismatched argument count in print statement. Expected %d, got %d.\n", expectedArgs, actualArgs);
            YYABORT;
        }
        
        $$ = createFormatStringNode($1, $3); 
    }
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
        int expectedArgs = countPlaceholders($3);
        int actualArgs = countArgs($5);

        if (expectedArgs != actualArgs) {
            fprintf(stderr, "Error: Mismatched argument count in scan statement. Expected %d, got %d.\n", expectedArgs, actualArgs);
            YYABORT;
        }

        $$ = createScanNode($3, $5);
    }
    ;
    

InputString:
    INPUT_STRING { $$ = $1; }
    ;

InputArgList:
      VarName {
          $$ = createVarRefNode($1);
      }
    | VarName COMMA InputArgList {
          $$ = createInputArgListNode(createVarRefNode($1), $3);
      }
    ;


Assignment:
      VarName ASSIGN AssnArg SEMICOLON
    {
        $$ = createAssignNode($1, $3);
    }
    | VarName ADD_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_ADD_ASSIGN, $1, $3);
    }
    | VarName SUB_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_SUB_ASSIGN, $1, $3);
    }
    | VarName MUL_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_MUL_ASSIGN, $1, $3);
    }
    | VarName DIV_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_DIV_ASSIGN, $1, $3);
    }
    | VarName MOD_ASSIGN AssnArg SEMICOLON
    {
        $$ = createOperatorAssignNode(NODE_MOD_ASSIGN, $1, $3);
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
        if (!is_valid_number_for_base($2, $4)) {
            fprintf(stderr, "Semantic Error: Number %d contains invalid digits for base %d.\n", $2, $4);
            YYABORT;
        }
        $$ = createNumberNode($2, $4);
    }
    ;

ConditionalStmt:
      IF_K LPAR Condition RPAR Block SEMICOLON %prec IF_PREC
    {
        $$ = createIfNode($3, $5, NULL);
    }
    | IF_K LPAR Condition RPAR Block ELSE_K Block SEMICOLON
    {
        $$ = createIfNode($3, $5, $7);
    }
    ;

Block:
    BEGIN_K StatementList END_K
    {
        $$ = createBlockNode($2);
    }
    ;

LoopStmt:
      WHILE_K LPAR Condition RPAR DO_K BEGIN_K StatementList END_K SEMICOLON
    {
        $$ = createWhileNode($3, createBlockNode($7));
    }
    | FOR_K VarName ASSIGN ArithmeticExpression TO_K ArithmeticExpression LoopOp ArithmeticExpression DO_K BEGIN_K StatementList END_K SEMICOLON
    {
        $$ = createForNode(createVarRefNode($2), $4, $6, $7, $8, $11);
    }
    ;

LoopOp:
      INC { $$ = INC; }
    | DEC { $$ = DEC; }
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
            default: opType = NODE_EQ;
        }
        $$ = createOperatorNode(opType, $1, $3);
    }
    ;

RelOp:
      EQ  { $$ = EQ; }
    | NEQ { $$ = NEQ; }
    | GT  { $$ = GT; }
    | LT  { $$ = LT; }
    | GEQ { $$ = GEQ; }
    | LEQ { $$ = LEQ; }
    ;

ArithmeticExpression:
      Term                                    { $$ = $1; }
    | ArithmeticExpression ADD_OP Term        {
        $$ = createOperatorNode(NODE_ADD, $1, $3);
    }
    | ArithmeticExpression SUB_OP Term        {
        $$ = createOperatorNode(NODE_SUB, $1, $3);
    }
    ;

Term:
      Factor                           { $$ = $1; }
    | Term MUL_OP Factor               {
        $$ = createOperatorNode(NODE_MUL, $1, $3);
    }
    | Term DIV_OP Factor               {
        $$ = createOperatorNode(NODE_DIV, $1, $3);
    }
    | Term MOD_OP Factor               {
        $$ = createOperatorNode(NODE_MOD, $1, $3);
    }
    ;

Factor:
      Primary                          { $$ = $1; }
    | SUB_OP Factor %prec UMINUS       {
        $$ = createOperatorNode(NODE_NEG, createNumberNode(0,10), $2);
    }
    ;

Primary:
      NUM                              { $$ = $1; }
    | VarName                          {
        $$ = createVarRefNode($1);
    }
    | LPAR ArithmeticExpression RPAR   {
        $$ = $2;
    }
    ;


%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }
    int result = yyparse();
    fclose(yyin);

    if (result == 0 && rootNode != NULL) {
        execute(rootNode->data.program.vars);
        printSymbolTable();
        execute(rootNode->data.program.stmts);
        printSymbolTable();
        freeAST(rootNode);
    }

    return result;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s\n", s);
}
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
extern int yylex();
extern int yylineno;
extern char* yytext;

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d near token '%s': %s\n", yylineno, yytext, s);
}

int syntax_errors = 0;

/* Symbol table for variable tracking */
#define MAX_SYMBOLS 100
char* symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

/* Add a variable to the symbol table */
void add_symbol(char* name) {
    if (symbol_count < MAX_SYMBOLS) {
        /* Check if symbol already exists */
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i], name) == 0) {
                return; /* Already exists */
            }
        }
        symbol_table[symbol_count] = strdup(name);
        symbol_count++;
    }
}

/* Check if a variable exists in the symbol table */
int symbol_exists(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], name) == 0) {
            return 1; /* Found */
        }
    }
    return 0; /* Not found */
}

/* Check if a number base is valid (2, 8, or 10) */
int is_valid_base(int base) {
    return (base == 2 || base == 8 || base == 10);
}
%}

%union {
    int int_val;
    char* str_val;
}

%token BEGIN_K END_K PROGRAM COLON SEMICOLON COMMA LPAR RPAR LBRACK RBRACK
%token INT CHAR PRINT SCAN VARDECL INC DEC
%token ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP
%token <str_val> ID STRING CHARACTER FORMAT_STRING INPUT_STRING
%token <int_val> NUMBER
%token IF_K ELSE_K WHILE_K FOR_K TO_K DO_K
%token EQ NEQ GT LT GEQ LEQ
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN

%type <int_val> NUM
%type <str_val> VarName VarNameDecl
%type <int_val> ArithmeticExpression Primary Factor Term


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
    { printf("Successfully parsed program structure\n"); }
    ;

VarDeclSection:
    BEGIN_K VARDECL COLON DeclList END_K VARDECL
    { printf("Successfully parsed variable declaration section\n"); }
    ;

DeclList:
      Decl DeclList
    | /* empty */
    ;

Decl:
    LPAR VarNameDecl COMMA Type RPAR SEMICOLON
    { printf("Parsed variable declaration: %s\n", $2); }
    ;

Type:
      INT { printf("Type: int\n"); }
    | CHAR { printf("Type: char\n"); }
    ;

VarNameDecl:
      ID                      
    {
        $$ = $1;
        add_symbol($1);
        printf("Variable name: %s\n", $1);
    }
    | ID LBRACK NUMBER RBRACK
    {
        $$ = $1;
        add_symbol($1);
        printf("Array declaration: %s[%d]\n", $1, $3);
    }
    ;

VarName:
      ID { 
        $$ = $1; 
        if (!symbol_exists($1)) {
            fprintf(stderr, "Semantic Error at line %d: Undeclared variable '%s'\n", yylineno, $1);
            syntax_errors++;
        }
      }
    | ID LBRACK ArithmeticExpression RBRACK { 
        $$ = $1; 
        if (!symbol_exists($1)) {
            fprintf(stderr, "Semantic Error at line %d: Undeclared variable '%s'\n", yylineno, $1);
            syntax_errors++;
        }
      }
    ;

StatementSection:
      StatementList { printf("Successfully parsed statement section\n"); }
    | /* empty */
    ;

StatementList:
      Statement StatementList
    | Statement
    ;

Statement:
      OutputStmt
    | InputStmt
    | Assignment
    | ConditionalStmt
    | LoopStmt
    ;

OutputStmt:
    PRINT LPAR PrintArg RPAR SEMICOLON
    { printf("Parsed print statement\n"); }
    ;

PrintArg:
      STRING { printf("Print string literal\n"); }
    | INPUT_STRING COMMA OutputArgList { printf("Print input format string with arguments\n"); }
    | FORMAT_STRING COMMA OutputArgList { printf("Print format string with arguments\n"); }
    ;

OutputArgList:
      OutputArg
    | OutputArg COMMA OutputArgList
    ;

OutputArg:
      ArithmeticExpression
    | STRING
    | CHARACTER
    ;

InputStmt:
    SCAN LPAR InputString COMMA InputArgList RPAR SEMICOLON
    { printf("Parsed scan statement\n"); }
    ;


InputString:
    INPUT_STRING
    ;

InputArgList:
      VarName { printf("Input to variable: %s\n", $1); }
    | VarName COMMA InputArgList { printf("Input to variable: %s\n", $1); }
    ;

Assignment:
      VarName ASSIGN AssnArg SEMICOLON
    { printf("Parsed assignment with :=\n"); }
    | VarName ADD_ASSIGN AssnArg SEMICOLON
    { printf("Parsed assignment with +=\n"); }
    | VarName SUB_ASSIGN AssnArg SEMICOLON
    { printf("Parsed assignment with -=\n"); }
    | VarName MUL_ASSIGN AssnArg SEMICOLON
    { printf("Parsed assignment with *=\n"); }
    | VarName DIV_ASSIGN AssnArg SEMICOLON
    { printf("Parsed assignment with /=\n"); }
    | VarName MOD_ASSIGN AssnArg SEMICOLON
    { printf("Parsed assignment with %%=\n"); }
    ;

AssnArg:
      STRING
    | CHARACTER
    | ArithmeticExpression
    ;

NUM:
      LPAR NUMBER COMMA NUMBER RPAR  
    { 
        if (!is_valid_base($4)) {
            fprintf(stderr, "Semantic Error at line %d: Invalid number base %d. Only bases 2, 8, and 10 are allowed.\n", yylineno, $4);
            syntax_errors++;
        }
        $$ = $2; 
        printf("Number: %d in base %d\n", $2, $4); 
    }
    ;

ConditionalStmt:
      IF_K LPAR Condition RPAR Block SEMICOLON %prec IF_PREC
    { printf("Parsed if statement\n"); }
    | IF_K LPAR Condition RPAR Block ELSE_K Block SEMICOLON
    { printf("Parsed if-else statement\n"); }
    ;

Block:
    BEGIN_K StatementList END_K
    { printf("Parsed block of statements\n"); }
    ;

LoopStmt:
      WHILE_K LPAR Condition RPAR BEGIN_K StatementList END_K SEMICOLON
    { printf("Parsed while loop\n"); }
    | FOR_K VarName ASSIGN ArithmeticExpression TO_K ArithmeticExpression LoopOp ArithmeticExpression DO_K BEGIN_K StatementList END_K SEMICOLON
    { printf("Parsed for loop\n"); }
    ;

LoopOp:
      INC { printf("Loop operator: inc\n"); }
    | DEC { printf("Loop operator: dec\n"); }
    ;

Condition:
      ArithmeticExpression RelOp ArithmeticExpression
    { printf("Parsed condition\n"); }
    ;

RelOp:
      EQ  { printf("Relational operator: =\n"); }
    | NEQ { printf("Relational operator: <>\n"); }
    | GT  { printf("Relational operator: >\n"); }
    | LT  { printf("Relational operator: <\n"); }
    | GEQ { printf("Relational operator: >=\n"); }
    | LEQ { printf("Relational operator: <=\n"); }
    ;

ArithmeticExpression:
      Term                                    { $$ = $1; }
    | ArithmeticExpression ADD_OP Term        { $$ = $1 + $3; printf("Addition\n"); }
    | ArithmeticExpression SUB_OP Term        { $$ = $1 - $3; printf("Subtraction\n"); }
    ;

Term:
      Factor                           { $$ = $1; }
    | Term MUL_OP Factor               { $$ = $1 * $3; printf("Multiplication\n"); }
    | Term DIV_OP Factor               { $$ = $1 / $3; printf("Division\n"); }
    | Term MOD_OP Factor               { $$ = $1 % $3; printf("Modulo\n"); }
    ;

Factor:
      Primary                          { $$ = $1; }
    | SUB_OP Factor %prec UMINUS       { $$ = -$2; printf("Unary minus\n"); }
    ;

Primary:
      NUM                              { $$ = $1; }
    | VarName                          { $$ = 0; /* Placeholder */ }
    | LPAR ArithmeticExpression RPAR   { $$ = $2; printf("Parenthesized expression\n"); }
    ;

%%

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }

    printf("Parsing input...\n");
    int result = yyparse();

    if (result == 0 && syntax_errors == 0) {
        printf("Parsing complete: Input is syntactically correct.\n");
        return 0;
    } else {
        printf("Parsing failed with %d errors.\n", syntax_errors);
        return 1;
    }
}

%{
#include "a.h"
#include "a.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern YYSTYPE yylval;
%}

%option noyywrap
%option yylineno

%%

\/\/[^\n]*           { printf("COMMENT: Single-line\n"); }      // Single-line comment
\/\*([^*]|\*+[^*/])*\*+\/   { printf("COMMENT: Multi-line\n"); }

"begin"           { printf("TOKEN: BEGIN_K\n"); return BEGIN_K; }
"end"             { printf("TOKEN: END_K\n"); return END_K; }
"program"         { printf("TOKEN: PROGRAM\n"); return PROGRAM; }
"VarDecl"         { printf("TOKEN: VARDECL\n"); return VARDECL; }
"int"             { printf("TOKEN: INT\n"); return INT; }
"char"            { printf("TOKEN: CHAR\n"); return CHAR; }
"print"           { printf("TOKEN: PRINT\n"); return PRINT; }
"scan"            { printf("TOKEN: SCAN\n"); return SCAN; }
"if"              { printf("TOKEN: IF_K\n"); return IF_K; }
"else"            { printf("TOKEN: ELSE_K\n"); return ELSE_K; }
"while"           { printf("TOKEN: WHILE_K\n"); return WHILE_K; }
"for"             { printf("TOKEN: FOR_K\n"); return FOR_K; }
"inc"             { printf("TOKEN: INC\n"); return INC; }
"dec"             { printf("TOKEN: DEC\n"); return DEC; }
"do"              { printf("TOKEN: DO_K\n"); return DO_K; }
"to"              { printf("TOKEN: TO_K\n"); return TO_K; }

":="              { printf("TOKEN: ASSIGN\n"); return ASSIGN; }
"+="              { printf("TOKEN: ADD_ASSIGN\n"); return ADD_ASSIGN; }
"-="              { printf("TOKEN: SUB_ASSIGN\n"); return SUB_ASSIGN; }
"*="              { printf("TOKEN: MUL_ASSIGN\n"); return MUL_ASSIGN; }
"/="              { printf("TOKEN: DIV_ASSIGN\n"); return DIV_ASSIGN; }
"%="              { printf("TOKEN: MOD_ASSIGN\n"); return MOD_ASSIGN; }

"+"               { printf("TOKEN: ADD_OP\n"); return ADD_OP; }
"-"               { printf("TOKEN: SUB_OP\n"); return SUB_OP; }
"*"               { printf("TOKEN: MUL_OP\n"); return MUL_OP; }
"/"               { printf("TOKEN: DIV_OP\n"); return DIV_OP; }
"%"               { printf("TOKEN: MOD_OP\n"); return MOD_OP; }

"<="              { printf("TOKEN: LEQ\n"); return LEQ; }
">="              { printf("TOKEN: GEQ\n"); return GEQ; }
">"               { printf("TOKEN: GT\n"); return GT; }
"<"               { printf("TOKEN: LT\n"); return LT; }
"="               { printf("TOKEN: EQ\n"); return EQ; }
"<>"              { printf("TOKEN: NEQ\n"); return NEQ; }

":"               { printf("TOKEN: COLON\n"); return COLON; }
";"               { printf("TOKEN: SEMICOLON\n"); return SEMICOLON; }
","               { printf("TOKEN: COMMA\n"); return COMMA; }
"("               { printf("TOKEN: LPAR\n"); return LPAR; }
")"               { printf("TOKEN: RPAR\n"); return RPAR; }
"["               { printf("TOKEN: LBRACK\n"); return LBRACK; }
"]"               { printf("TOKEN: RBRACK\n"); return RBRACK; }

[0-9]+            {
                    yylval.int_val = atoi(yytext);
                    printf("TOKEN: NUMBER (%d)\n", yylval.int_val);
                    return NUMBER;
                  }

\'([^\\\']|\\[ntbrfavo\'\"\\])\'  {
                    yylval.str_val = strdup(yytext);
                    printf("TOKEN: CHARACTER (%s)\n", yytext);
                    return CHARACTER;
                  }

\"@((,@))*\" {
                    yylval.str_val = strdup(yytext);
                    printf("TOKEN: INPUT_STRING (%s)\n", yytext);
                    return INPUT_STRING;
                  }

\"([^\\\"]|\\[ntbrfavo\'\"\\])*\"  {
                    yylval.str_val = strdup(yytext);
                    if (strchr(yytext, '@')) {
                        printf("TOKEN: FORMAT_STRING (%s)\n", yytext);
                        return FORMAT_STRING;
                    } else {
                        printf("TOKEN: STRING (%s)\n", yytext);
                        return STRING;
                    }
                  }

[a-z][a-z0-9_]*   {
                    yylval.str_val = strdup(yytext);
                    printf("TOKEN: ID (%s)\n", yytext);
                    return ID;
                  }

[ \t\r]+          ; // ignore whitespace

\n                { yylineno++; }

.                 {
                    printf("ERROR: Unknown token '%s'\n", yytext);
                    return 0;
                  }

%%
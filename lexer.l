%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern YYSTYPE yylval;
%}

%option noyywrap
%option yylineno

%%

\/\/[^\n]*           { printf("COMMENT: Single-line at line %d\n", yylineno); }      // Single-line comment
\/\*([^*]|\*+[^*/])*\*+\/   {
                          int newline_count = 0;
                          for (char* p = yytext; *p; p++) {
                              if (*p == '\n') newline_count++;
                          }
                          yylineno += newline_count;
                          printf("COMMENT: Multi-line at lines %d to %d\n", yylineno - newline_count, yylineno);
                      }

"begin"           { printf("TOKEN: BEGIN_K at line %d\n", yylineno); return BEGIN_K; }
"end"             { printf("TOKEN: END_K at line %d\n", yylineno); return END_K; }
"program"         { printf("TOKEN: PROGRAM at line %d\n", yylineno); return PROGRAM; }
"VarDecl"         { printf("TOKEN: VARDECL at line %d\n", yylineno); return VARDECL; }
"int"             { printf("TOKEN: INT at line %d\n", yylineno); return INT; }
"char"            { printf("TOKEN: CHAR at line %d\n", yylineno); return CHAR; }
"print"           { printf("TOKEN: PRINT at line %d\n", yylineno); return PRINT; }
"scan"            { printf("TOKEN: SCAN at line %d\n", yylineno); return SCAN; }
"if"              { printf("TOKEN: IF_K at line %d\n", yylineno); return IF_K; }
"else"            { printf("TOKEN: ELSE_K at line %d\n", yylineno); return ELSE_K; }
"while"           { printf("TOKEN: WHILE_K at line %d\n", yylineno); return WHILE_K; }
"for"             { printf("TOKEN: FOR_K at line %d\n", yylineno); return FOR_K; }
"inc"             { printf("TOKEN: INC at line %d\n", yylineno); return INC; }
"dec"             { printf("TOKEN: DEC at line %d\n", yylineno); return DEC; }
"do"              { printf("TOKEN: DO_K at line %d\n", yylineno); return DO_K; }
"to"              { printf("TOKEN: TO_K at line %d\n", yylineno); return TO_K; }

":="              { printf("TOKEN: ASSIGN at line %d\n", yylineno); return ASSIGN; }
"+="              { printf("TOKEN: ADD_ASSIGN at line %d\n", yylineno); return ADD_ASSIGN; }
"-="              { printf("TOKEN: SUB_ASSIGN at line %d\n", yylineno); return SUB_ASSIGN; }
"*="              { printf("TOKEN: MUL_ASSIGN at line %d\n", yylineno); return MUL_ASSIGN; }
"/="              { printf("TOKEN: DIV_ASSIGN at line %d\n", yylineno); return DIV_ASSIGN; }
"%="              { printf("TOKEN: MOD_ASSIGN at line %d\n", yylineno); return MOD_ASSIGN; }

"+"               { printf("TOKEN: ADD_OP at line %d\n", yylineno); return ADD_OP; }
"-"               { printf("TOKEN: SUB_OP at line %d\n", yylineno); return SUB_OP; }
"*"               { printf("TOKEN: MUL_OP at line %d\n", yylineno); return MUL_OP; }
"/"               { printf("TOKEN: DIV_OP at line %d\n", yylineno); return DIV_OP; }
"%"               { printf("TOKEN: MOD_OP at line %d\n", yylineno); return MOD_OP; }

"<="              { printf("TOKEN: LEQ at line %d\n", yylineno); return LEQ; }
">="              { printf("TOKEN: GEQ at line %d\n", yylineno); return GEQ; }
">"               { printf("TOKEN: GT at line %d\n", yylineno); return GT; }
"<"               { printf("TOKEN: LT at line %d\n", yylineno); return LT; }
"="               { printf("TOKEN: EQ at line %d\n", yylineno); return EQ; }
"<>"              { printf("TOKEN: NEQ at line %d\n", yylineno); return NEQ; }

":"               { printf("TOKEN: COLON at line %d\n", yylineno); return COLON; }
";"               { printf("TOKEN: SEMICOLON at line %d\n", yylineno); return SEMICOLON; }
","               { printf("TOKEN: COMMA at line %d\n", yylineno); return COMMA; }
"("               { printf("TOKEN: LPAR at line %d\n", yylineno); return LPAR; }
")"               { printf("TOKEN: RPAR at line %d\n", yylineno); return RPAR; }
"["               { printf("TOKEN: LBRACK at line %d\n", yylineno); return LBRACK; }
"]"               { printf("TOKEN: RBRACK at line %d\n", yylineno); return RBRACK; }

[0-9]+            { 
                    yylval.int_val = atoi(yytext);
                    printf("TOKEN: NUMBER (%d) at line %d\n", yylval.int_val, yylineno);
                    return NUMBER;
                  }

\'([^\\\']|\\[ntbrfavo\'\"\\])\'  {
                    yylval.str_val = strdup(yytext);
                    printf("TOKEN: CHARACTER (%s) at line %d\n", yytext, yylineno);
                    return CHARACTER;
                  }

\"@((,@))*\" {
                    yylval.str_val = strdup(yytext);
                    printf("TOKEN: INPUT_STRING (%s) at line %d\n", yytext, yylineno);
                    return INPUT_STRING;
                  }

\"([^\\\"]|\\[ntbrfavo\'\"\\])*\"  {
                    yylval.str_val = strdup(yytext);
                    if (strchr(yytext, '@')) {
                        printf("TOKEN: FORMAT_STRING (%s) at line %d\n", yytext, yylineno);
                        return FORMAT_STRING;
                    } else {
                        printf("TOKEN: STRING (%s) at line %d\n", yytext, yylineno);
                        return STRING;
                    }
                  }

[a-z][a-z0-9_]*   {
                    yylval.str_val = strdup(yytext);
                    printf("TOKEN: ID (%s) at line %d\n", yytext, yylineno);
                    return ID;
                  }

[ \t\r]+          ; // ignore whitespace

\n                { yylineno++; }

.                 {
                    printf("ERROR: Unknown token '%s' at line %d\n", yytext, yylineno);
                    return 0;
                  }

%%


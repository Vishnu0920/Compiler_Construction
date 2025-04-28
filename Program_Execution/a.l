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

\/\/[^\n]*           { /* Single-line comment */ }     
\/\*([^*]|\*+[^*/])*\*+\/   { /* Multi-line comment */ }

"begin"           { return BEGIN_K; }
"end"             { return END_K; }
"program"         { return PROGRAM; }
"VarDecl"         { return VARDECL; }
"int"             { return INT; }
"char"            { return CHAR; }
"print"           { return PRINT; }
"scan"            { return SCAN; }
"if"              { return IF_K; }
"else"            { return ELSE_K; }
"while"           { return WHILE_K; }
"for"             { return FOR_K; }
"inc"             { return INC; }
"dec"             { return DEC; }
"do"              { return DO_K; }
"to"              { return TO_K; }

":="              { return ASSIGN; }
"+="              { return ADD_ASSIGN; }
"-="              { return SUB_ASSIGN; }
"*="              { return MUL_ASSIGN; }
"/="              { return DIV_ASSIGN; }
"%="              { return MOD_ASSIGN; }

"+"               { return ADD_OP; }
"-"               { return SUB_OP; }
"*"               { return MUL_OP; }
"/"               { return DIV_OP; }
"%"               { return MOD_OP; }

"<="              { return LEQ; }
">="              { return GEQ; }
">"               { return GT; }
"<"               { return LT; }
"="               { return EQ; }
"<>"              { return NEQ; }

":"               { return COLON; }
";"               { return SEMICOLON; }
","               { return COMMA; }
"("               { return LPAR; }
")"               { return RPAR; }
"["               { return LBRACK; }
"]"               { return RBRACK; }

[0-9]+            {
                    yylval.int_val = atoi(yytext);
                    return NUMBER;
                  }

\'([^\\\']|\\[ntbrfavo\'\"\\])\'  {
                    yylval.str_val = strdup(yytext);
                    return CHARACTER;
                  }

\"@([ \t]*,[ \t]*@)*[ \t]*\" {
    int len = strlen(yytext);
    char* stripped = (char*)malloc(len - 1);
    strncpy(stripped, yytext + 1, len - 2);
    stripped[len - 2] = '\0';
    yylval.str_val = stripped;
    return INPUT_STRING;
}

\"([^\\\"]|\\[ntbrfavo\'\"\\])*\"  {
    int len = strlen(yytext);
    char* stripped = (char*)malloc(len - 1);
    strncpy(stripped, yytext + 1, len - 2);
    stripped[len - 2] = '\0';
    yylval.str_val = stripped;
    if (strchr(stripped, '@')) {
        return FORMAT_STRING;
    } else {
        return STRING;
    }
}

[a-z][a-z0-9]*[_]?[a-z0-9]* {
                    yylval.str_val = strdup(yytext);
                    return ID;
                  }

[ \t\r]+          ; // ignore whitespace

\n                { yylineno++; }

.                 {
                    return 0;
                  }

%% 

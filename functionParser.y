%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex(void);
void yyerror(const char* s);

%}

%token RETYPE TYPE ID OB CB COMMA SEMCOL NL

%%
stmt: def NL	{printf("Succesffuly declared function!\n"); return 1;}
    ;

def: RETYPE OB argList CB
   ;
   
argList: TYPE ID 		{}
       | TYPE ID COMMA argList  {}
       ;
%%

int main()
{
	printf("Enter Expression: ");
	yyparse();
	return 0;
}

void yyerror(const char *s)
{
	fprintf(stderr, "Error: %s\n", s);
	exit(1);
}

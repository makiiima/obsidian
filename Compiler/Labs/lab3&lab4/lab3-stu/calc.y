%{
	#include<stdio.h>

	int yylex(void);
	int yyerror(char* s);
%}
%token INTEGER
%left '+' '-'
%left '*' '/'

%%

lines:
	 lines state '\n'
	 |
	 ;

state:
	 expr			{ printf("%d\n",$1); }
	 |
	 ;

expr:
	INTEGER
	| expr '+' INTEGER	{ $$ = $1 + $3; }
	| expr '-' INTEGER	{ $$ = $1 - $3; }
	| expr '*' INTEGER{ $$ = $1 * $3; }
	| expr '/' INTEGER	{ $$ = $1 / $3; }
	| expr '^' INTEGER	{ $$ = $1 ^ $3; }
	| '-' INTEGER		{ $$ = -$2; }
	| '(' expr ')'	{ $$ = $2; }
	;

%%


int main(int argc, const char *argv[]) {
	yyparse();
	return 0;
}


%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex(void);
void yyerror(char *);

%}

%token NUM
%token PLUS MINUS TIMES DIVIDE POWER UMINUS LP RP EOL

%%

input:
    | input line
    ;

line:
    exp EOL { printf("%d\n", (int)$1); }
    ;

exp:
    term
    | exp PLUS term { $$ = $1 + $3; }
    | exp MINUS term { $$ = $1 - $3; }
    ;

term:
    factor
    | term TIMES factor { $$ = $1 * $3; }
    | term DIVIDE factor { $$ = $1 / $3; }
    ;

factor:
    base
    | base POWER factor { $$ = pow($1, $3); }
    ;

base:
    NUM
    | MINUS base %prec UMINUS { $$ = -$2; }
    | LP exp RP { $$ = $2; }
    ;

%%

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

int main()
{
    yyparse();
    return 0;
}

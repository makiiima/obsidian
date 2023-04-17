%{
#include <stdio.h>
#include "calc.tab.h"
%}

%%

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIVIDE; }
"^" { return POWER; }
"(" { return LP; }
")" { return RP; }
[0-9]+ { yylval = atoi(yytext); return NUM; }
[ \t] { ; }
\n { return EOL; }
. { printf("Invalid character %c\n", *yytext); }

%%

int yywrap()
{
    return 1;
}

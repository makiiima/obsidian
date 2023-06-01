%{
#include "compiler.tab.h"
%}
%option noinput nounput nodefault

%%
"int"   { return INT; }
"main"  { return MAIN; }
"return" { return RETURN; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
[0-9]+  { yylval.num = atoi(yytext); return NUMBER; }
.       { return yytext[0]; }
%%

int yywrap() { return 1; }

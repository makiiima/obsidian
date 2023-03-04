%{
	#include"calc.tab.h"
%}
%{
   #include <stdio.h>
   void yyerror(const char* msg) {
      fprintf(stderr, "%s\n", msg);
   }
   int yylex();
%}

%%
[0-9]+ {
	yylval = atoi(yytext);
	return INTEGER;
}

["+""-""*""/""=""("")"\n] {
	return *yytext;
}

[ \t] {
}

%%

int yywrap(){
	return 1;
}

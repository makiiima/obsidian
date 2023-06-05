%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #inlcude "parser.hpp"
%}

DIGITS [0-9]+
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%option yylineno
%option outfile="lexer.cpp"

%%

"(" { return LPAREN; }
")" { return RPAREN; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"[" { return LBRACKET; }
"]" { return RBRACKET; }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MUL; }
"/" { return DIV; }
"%" { return MOD; }

"&&" { return AND; }
"||" { return OR; }
"!" { return NOT; }

">" { return GT; }
">=" { return GE; }
"<" { return LT; }
"<=" { return LE; }
"==" { return EQ; }
"!=" { return NE; }

";" { return SEMICOLON; }
"," { return COMMA; }
"=" { return ASSIGN; }

"int" { return INT; }
"char" { return CHAR; }

"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"break" { return BREAK; }
"continue" { return CONTINUE; }
"return" { return RETURN; }

IDENTIFIER {yylval.id = new std::string(yytext, yyleng); return IDENTIFIER;}
DIGITS {yylval.intval = atoi(yytext); return DIGITS;}

[ \b\t\n\r] { /* ignore whitespace */ }

%%

int yywrap() {
    return 1;
}

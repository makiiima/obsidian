%{
    #include <stdio.h>
    #include <stdlib.h>
    #include<iostream>
    #include "AST.hpp"
    #include "parser.hpp"
    
%}
 
D [0-9]
H [0-9a-fA-F]

%option yylineno
%option outfile="lexer.cpp"

%%



"["           {return LBRACKET;}
"]"           {return RBRACKET;}
"("           {return LPAREN;}
")"           {return RPAREN;}
"{"           {return LBRACE;}
"}"           {return RBRACE;}

"+"           {return ADD;}
"++"          {return INC;}
"+="          {return ADDEQ;}
"-"           {return SUB;}
"--"          {return DEC;}
"-="          {return SUBEQ;}
"*"           {return MUL;}
"*="          {return MULEQ;}
"/"           {return DIV;}
"/="          {return DIVEQ;}
"%"           {return MOD;}
"%="          {return MODEQ;}

"&"           {return BITAND_ADDRESS;}
"&&"          {return AND;}
"&="          {return BITANDEQ;}
"|"           {return BITOR;}
"||"          {return OR;}
"|="          {return BITOREQ;}
"!"           {return NOT;}
"^"           {return XOR;}
"^="          {return XOREQ;}

"<<"          {return LSHIFT;}
"<<="         {return LSHIFTEQ;}
">>"          {return RSHIFT;}
">>="         {return RSHIFTEQ;}

">"           {return GT;}
">="          {return GEQ;}
"<"           {return LT;}
"<="          {return LEQ;}
"=="          {return EQ;}
"!="          {return NEQ;}

"."           {return DOT;}
"->"          {return MEMBEROF;}
"~"           {return BITNOT;}
"sizeof"      {return SIZEOF;}
"?"           {return QUE;}
":"           {return COLON;}
";"           {return SEMI;}
"="           {return ASSIGN;}
","           {return COMMA;}

"bool"        {return BOOL;}
"int"         {return INT;}
"long"        {return LONG;}
"float"       {return FLOAT;}
"double"      {return DOUBLE;}
"char"        {return CHAR;}
"unsigned"    {return UNSIGNED;}
"struct"      {return STRUCT;}
"union"       {return UNION;}
"enum"        {return ENUM;}
"true"        {return TRUE;}
"false"       {return FALSE;}
"void"        {return VOID;}
"const"       {return CONST;}

"if"          {return IF;}
"else"        {return ELSE;}
"for"         {return FOR;}
"while"       {return WHILE;}
"do"          {return DO;}
"break"       {return BREAK;}
"continue"    {return CONTINUE;}
"switch"      {return SWITCH;}
"case"        {return CASE;}
"default"     {return DEFAULT;}
"return"      {return RETURN;}

"#define"     {return DEFINE;}

[a-zA-Z_][a-zA-Z_{D}]*           {yylval.id = new std::string(yytext, yyleng);return IDENTIFIER;}
0|[1-9]{D}*                      {yylval.intval = atoi(yytext);return INT_CONST;}       
0[0-7]*                          {yylval.intval = atoi(yytext);return INT_CONST;}
0[xX]{H}+                        {yylval.intval = atoi(yytext);return INT_CONST;}
0b[01]*                          {yylval.intval = atoi(yytext);return INT_CONST;}
{D}*\.{D}+                       {yylval.doubleval = atof(yytext);return DOUBLE_CONST;}
{D}+\.{D}+[eE][+-]?{D}+          {yylval.doubleval = atof(yytext);return DOUBLE_CONST;}
\'.'\|\'\\.'\                    {yylval.charval = yytext[1];return CHAR_CONST;}
\"(\\.|[^"\\])*\"                {yylval.stringval = new std::string(yytext, yyleng);return STRING_CONST;}

"//".*                                 {;}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"      {;}

[ \b\t\n\r]                            {;}

%%

int yywrap()
{
  return 1;
}
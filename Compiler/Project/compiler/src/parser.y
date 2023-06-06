%{
  #include <iostream>
  #include <string>
  #include "ast.hpp"
  extern int yylex(void);
  int yyerror(char* s){fprintf(stderr,"%s\n",s);return 0;}
  using namespace std;
%}

%output "parser.cpp"

%union{
  std::string* id;
  int int_val;
  char char_val;
  std::string* string_val;
  AST::Program *program;
  AST::Define_List *declist;
  AST::Fun_Imp *funimp;
  AST::Block *block;
  AST::Para_List *paralist;
  AST::Var_Dec *vardec;
  AST::Stat_List *statlist;
  AST::Stat *stat;
  AST::Exp *exp;
  AST::Exp_List *explist;
  AST::Specifier *specifier;
  AST::Constant *constant;
}

%token <id> IDENTIFIER
%token <int_val> INT_CONST
%token <char_val> CHAR_COSNT
%token <string_val> STRING_CONST
%token LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE 
       ADD INC ADDEQ SUB DEC SUBEQ MUL MULEQ DIV DIVEQ MOD MODEQ 
       BITAND_ADDRESS AND BITANDEQ BITOR OR BITOREQ NOT XOR XOREQ
       LSHIFT LSHIFTEQ RSHIFT RSHIFTEQ
       GT GEQ LT LEQ EQ NEQ
       DOT MEMBEROF BITNOT SIZEOF QUE COLON SEMI ASSIGN COMMA
       BOOL INT LONG FLOAT DOUBLE CHAR UNSIGNED STRUCT UNION ENUM TRUE FALSE VOID CONST
       IF ELSE FOR WHILE DO BREAK CONTINUE SWITCH CASE DEFAULT RETURN DEFINE

%left COMMA
%right ASSIGN DIVEQ MULEQ MODEQ ADDEQ SUBEQ LSHIFTEQ RSHIFTEQ BITANDEQ BITXOREQ BITOREQ
%right QUE COL
%left  OR
%left  AND
%left  BITOR
%left  BITXOR
%left  BITAND_ADDRESS
%left  EQ NEQ
%left  GT GEQ LT LEQ
%left  LSHIFT RSHIFT
%left  ADD SUB
%left  MUL DIV
%right INC DEC NOT BITNOT SIZEOF
%left LBRACKET RBRACKET LPAREN RPAREN DOT MEMBEROF

%type<program>                  Program
%type<declist>                  DecList
%type<funimp>                   FunImp
%type<block>                    Block
%type<paralist>                 ParaList
%type<vardec>                   VarDec
%type<statlist>                 StatList
%type<stat>                     Stat
%type<exp>                      Exp
%type<explist>                  ExpList
%type<specifier>                Specifier
%type<constant>                 Constant

%start Program
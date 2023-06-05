%{
    #include <iostream>
    #include <string>
    #include "AST.hpp"
    extern int yylex(void);
    int yyerror(char* s){fprintf(stderr,"%s\n",s);return 0;}
    AST::Program* root;
    using namespace std;
    using namespace AST;
%}

%output "parser.cpp"

%union {
    std::string* id;
    int intval;
    double doubleval;
    char charval;
    std::string* stringval;
    AST::Program *program;
    AST::Define_List *declist;
    AST::Fun_Imp *funimp;
    AST::Block *block;
    AST::Para_List *paralist;
    AST::Var_Dec *vardec;
//    Var_List *varlist;
//    Var_Init *varinit;
    AST::Stat_List *statlist;
    AST::Stat *stat;
    AST::Exp *exp;
    AST::Exp_List *explist;
    AST::Specifier *specifier;
    AST::Constant *constant;
}

%token <id> IDENTIFIER
%token <intval> INT_CONST
%token <doubleval> DOUBLE_CONST
%token <charval> CHAR_CONST
%token <stringval> STRING_CONST
%token LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE 
       ADD INC ADDEQ SUB DEC SUBEQ MUL MULEQ DIV DIVEQ MOD MODEQ 
       BITAND_ADDRESS AND BITANDEQ BITOR OR BITOREQ NOT XOR XOREQ
       LSHIFT LSHIFTEQ RSHIFT RSHIFTEQ
       GT GEQ LT LEQ EQ NEQ
       DOT MEMBEROF BITNOT SIZEOF QUE COLON SEMI ASSIGN COMMA
       BOOL INT LONG FLOAT DOUBLE CHAR UNSIGNED STRUCT UNION ENUM TRUE FALSE VOID CONST
       IF ELSE FOR WHILE DO BREAK CONTINUE SWITCH CASE DEFAULT RETURN DEFINE

%left  COMMA
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
//%type<varlist>                  VarList
//%type<varinit>                  VarInit
%type<statlist>                 StatList
%type<stat>                     Stat
%type<exp>                      Exp
%type<explist>                  ExpList
%type<specifier>                Specifier
%type<constant>                 Constant


%start Program

%%

Program:        DecList                                                         {root = $$ = new Program($1);}
                ;

DecList:        DecList VarDec                                                  {$$ = $1; $$->adddefine($2);}
 //               | DecList ConstructDec
                | DecList FunImp                                                {$$ = $1; $$->adddefine($2);}
                |                                                               {$$ = new Define_List();}
                ;

FunImp:         Specifier IDENTIFIER LPAREN ParaList RPAREN Block               {$$ = new Fun_Imp($1, *$2, $4, $6);}
                | Specifier IDENTIFIER LPAREN VOID RPAREN Block                 {$$ = new Fun_Imp($1, *$2, $6);}
                ;

Block:          LBRACE StatList RBRACE                                          {$$ = new Block($2);}
                ;

//int a, char c
ParaList:       ParaList COMMA Specifier IDENTIFIER                             {$$ = $1; $$->addpara($3, *$4);}
                | Specifier IDENTIFIER                                          {$$ = new Para_List(); $$->addpara($1, *$2);}                                                                 
                ;

//int a, b = 1;
VarDec:         Specifier IDENTIFIER SEMI                                          {$$ = new Var_Dec($1, *$2);}
                ;

//VarList:        VarList COMMA VarInit                                           {$$ = $1; $$->addvar($3);}
//                | VarInit                                                       {$$ = new Var_List(); $$->addvar($1);}
  //              ;

//VarInit:        IDENTIFIER ASSIGN Exp                                           {$$ = new Var_Init($1, $3);}
//                | IDENTIFIER                                                    {$$ = new Var_Init($1);}
//                ;

// ConstructDec:   StructDec
//                 | UnionDec
//                 | EnumDec
//                 ;

// StructDec:      STRUCT IDENTIFIER LBRACE MemberDecList RBRACE SEMI
//                 | STRUCT IDENTIFIER
//                 ;

// UnionDec:       UNION IDENTIFIER LBRACE MemberDecList RBRACE
//                 | UNION IDENTIFIER
//                 ;

// EnumDec:        ENUM IDENTIFIER LBRACE Members RBRACE SEMI
//                 ;

// int a, b;
// char c;
//MemberDecList:  MemberDec SEMI MemberDecList
//                | MemberDec
//                 ;

// int a, b;
//MemberDec:      Specifier Members SEMI
//                 ;

//a, b
//Members:        Members COMMA IDENTIFIER
//                 ;

StatList:       StatList Stat                                                   {$$ = $1; $$->addstat($2);}
                | Stat                                                          {$$ = new Stat_List(); $$->addstat($1);}
                ;

Stat:           Exp SEMI                                                        {$$ = $1;}
                | RETURN Exp SEMI                                               {$$ = new Stat_Return($2);}
                | IF LPAREN Exp RPAREN Block                                    {$$ = new Stat_If($3, $5);}
                | IF LPAREN Exp RPAREN Block ELSE Block                         {$$ = new Stat_IfElse($3, $5, $7);}
                | FOR LPAREN Exp SEMI Exp SEMI Exp RPAREN Block                 {$$ = new Stat_For($3, $5, $7, $9);}
                | WHILE LPAREN Exp RPAREN Block                                 {$$ = new Stat_While($3, $5);}
                | DO SEMI Block WHILE LPAREN Exp RPAREN SEMI                    {$$ = new Stat_DoWhile($6, $3);}
//                | SWITCH LPAREN Exp RPAREN COLON LBRACE CaseList RBRACE
                | VarDec                                                        {$$ = $1;}
//                | StructDec
                ;

// CaseList:       CASE Exp COLON StatList CaseList
//                 | DEFAULT COLON StatList
//                 ;

Exp:            Exp ADD Exp                                                     {$$ = new Exp_Bin("ADD", $1, $3);}
                | Exp SUB Exp                                                   {$$ = new Exp_Bin("SUB", $1, $3);}
                | Exp MUL Exp                                                   {$$ = new Exp_Bin("MUL", $1, $3);}
                | Exp DIV Exp                                                   {$$ = new Exp_Bin("DIV", $1, $3);}
                | Exp MOD Exp                                                   {$$ = new Exp_Bin("MOD", $1, $3);}
                | Exp BITAND_ADDRESS Exp                                        {$$ = new Exp_Bin("BITAND_ADDRESS", $1, $3);}
                | Exp AND Exp                                                   {$$ = new Exp_Bin("AND", $1, $3);}
                | Exp BITOR Exp                                                 {$$ = new Exp_Bin("BITOR", $1, $3);}
                | Exp OR Exp                                                    {$$ = new Exp_Bin("OR", $1, $3);}
                | Exp XOR Exp                                                   {$$ = new Exp_Bin("XOR", $1, $3);}
                | Exp LSHIFT Exp                                                {$$ = new Exp_Bin("LSHIFT", $1, $3);}
                | Exp RSHIFT Exp                                                {$$ = new Exp_Bin("RSHIFT", $1, $3);}
                | Exp GT Exp											        {$$ = new Exp_Bin("GT", $1, $3);} 
                | Exp GEQ Exp											        {$$ = new Exp_Bin("GEQ", $1, $3);}  
                | Exp LT Exp											        {$$ = new Exp_Bin("LT", $1, $3);}  
                | Exp LEQ Exp											        {$$ = new Exp_Bin("LEQ", $1, $3);}  
                | Exp EQ Exp											        {$$ = new Exp_Bin("EQ", $1, $3);}  
                | Exp NEQ Exp											        {$$ = new Exp_Bin("NEQ", $1, $3);}  

                | Exp ADDEQ Exp                                                 {$$ = new Exp_Bin("ADDEQ", $1, $3);}
                | Exp SUBEQ Exp                                                 {$$ = new Exp_Bin("SUBEQ", $1, $3);}
                | Exp MULEQ Exp                                                 {$$ = new Exp_Bin("MULEQ", $1, $3);}
                | Exp DIVEQ Exp                                                 {$$ = new Exp_Bin("DIVEQ", $1, $3);}
                | Exp MODEQ Exp                                                 {$$ = new Exp_Bin("MODEQ", $1, $3);}
                | Exp BITANDEQ Exp                                              {$$ = new Exp_Bin("BITANDEQ", $1, $3);}
                | Exp BITOREQ Exp                                               {$$ = new Exp_Bin("BITOREQ", $1, $3);}
                | Exp BITXOR Exp                                                {$$ = new Exp_Bin("BITXOREQ", $1, $3);}
                | Exp LSHIFTEQ Exp                                              {$$ = new Exp_Bin("LSHIFTEQ", $1, $3);}
                | Exp RSHIFTEQ Exp                                              {$$ = new Exp_Bin("RSHIFTEQ", $1, $3);}

                | NOT Exp                                                       {$$ = new Exp_Uni("NOT", $2);}
                | BITNOT Exp                                                    {$$ = new Exp_Uni("BITNOT", $2);}

                | Exp INC                                                       {$$ = new Exp_Uni("POSTFIX_INC", $1);}
                | INC Exp                                                       {$$ = new Exp_Uni("PREFIX_INC", $2);}
                | Exp DEC                                                       {$$ = new Exp_Uni("POSTFIX_DEC", $1);}
                | DEC Exp                                                       {$$ = new Exp_Uni("PREFIX_DEC", $2);}

                // | BITAND_ADDRESS Exp %pred
                // | Exp DOT IDENTIFIER
                // | Exp MEMBEROF IDENTIFIER
                // | SIZEOF LPAREN IDENTIFIER RPAREN 
                // | SIZEOF Exp
                // | SIZEOF LPAREN Exp RPAREN
                | Exp QUE Exp COL Exp                                           {$$ = new Exp_Con($1, $3, $5);}
                | Exp ASSIGN Exp                                                {$$ = new Exp_Assign($1, $3);}
             //   | Exp COMMA Exp                                                 {$$ = new Exp_Comma($1, $3);}
                | LPAREN Exp RPAREN                                             {$$ = $2;}
                | IDENTIFIER                                                    {$$ = new Exp_ID(*$1);}
                | Constant                                                      {$$ = $1;}
                | IDENTIFIER LPAREN ExpList RPAREN                              {$$ = new Exp_Func(*$1, $3);}
                ;

ExpList:        ExpList COMMA Exp                                               {$$ = $1; $$->addexp($3);}
                | Exp                                                           {$$ = new Exp_List(); $$->addexp($1);}

                ;

Specifier:      BOOL                                                            {$$ = new Specifier("BOOL");}
                | INT                                                           {$$ = new Specifier("INT");}
                | LONG                                                          {$$ = new Specifier("LONG");}
                | FLOAT                                                         {$$ = new Specifier("FLOAT");}
                | DOUBLE                                                        {$$ = new Specifier("DOUBLE");}
                | CHAR                                                          {$$ = new Specifier("CHAR");}
                | UNSIGNED INT                                                  {$$ = new Specifier("UNSIGNED INT");}
                | VOID                                                          {$$ = new Specifier("VOID");}
                // | StructDec
                // | UnionDec
                // | EnumDec
                ;

Constant:       TRUE                                                            {$$ = new Constant_Bool(true);}
                | FALSE                                                         {$$ = new Constant_Bool(false);}
                | INT_CONST                                                     {$$ = new Constant_Int($1);}
                | DOUBLE_CONST                                                  {$$ = new Constant_Double($1);}
                | CHAR_CONST                                                    {$$ = new Constant_Char($1);}
                | STRING_CONST                                                  {$$ = new Constant_String(*$1);}
                ;

%%

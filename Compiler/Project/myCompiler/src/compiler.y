%{

#include <iostream>
using namespace std;
#include "../src/ast.hpp"
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(std::unique_ptr<BaseAST> ast, const char* s);

%}

%union {
    std::string* str_val;
    int int_val;
    BaseAST* ast_val;
}
%parse-param { std::unique_ptr<BaseAST> &ast }

%token <ast_val>INT MAIN RETURN
%token <int_val> NUMBER
%token LBRACE RBRACE
%type <ast_val> CompUnit FuncDef FuncType Ident Block Stmt


%%

CompUnit: FuncDef{
    auto comp_unit = make_unique<CompUnitAST>();
    comp_unit->func_def = unique_ptr<BaseAST>($1);
    ast = std::move(comp_unit);
}
    ;

FuncDef: FuncType Ident '(' ')' Block
{
    auto ast = new FuncDefAST();
    ast->func_type = unique_ptr<BaseAST>($1);
    ast->ident = $2;
    ast->block = unique_ptr<BaseAST>($5);
    $$ = ast;
}
    ;

FuncType: INT
{
    auto ast = new FuncTypeAST();
    string type = "i32";
    ast->type = type;
    $$ = ast;
}
    ;

Ident: MAIN
    ;

Block: LBRACE Stmt RBRACE
{
    auto ast = new BlockAST();
    ast->stmt = unique_ptr<BaseAST>($2);
    $$ = ast;
}
    ;

Stmt: RETURN NUMBER ';'
    {
        auto ast = new StmtAST();
        ast->number = $2;
        $$=ast;
    }
    ;

%%


void yyerror(std::unique_ptr<BaseAST> ast,const char* s) {
    cerr << "Error: " << s << endl;
    exit(1);
}

#include<iostream>
#include<stack>
#include<map>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;
//Symbol table
class Symbol {
public:
    void* Content;
	std::string Type;
	Symbol(void) : Content(NULL), Type("UNDEFINED") {}
	Symbol(Function* Func) : Content(Func), Type("FUNCTION") {}
	//Symbol(Type* Ty) : Content(Ty), Type("TYPE") {}
	void* Getcontent(void) { return Content ; }
};
using SymbolTable = std::map<std::string, Symbol>;



class Symbol_Stack
{
public:
    std::stack<SymbolTable*> SymbolTableStack;
    SymbolTable*  SymbolTable_Now;
    void Push_SymbolTable(SymbolTable* t){SymbolTableStack.push(t);}
    SymbolTable* Top_SymbolTable(void){return SymbolTableStack.top();}
    void* Pop_SymbolTable(void){SymbolTableStack.pop();}
    // void Goin_Scope();
    // void Leave_Scope();
    // bool If_Defined_Inscope();

};


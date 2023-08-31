#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include <unistd.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>


#include "AST.hpp"
extern llvm::LLVMContext Context;
extern llvm::IRBuilder<> IRBuilder;

class CodeGenerator 
{
public:
	llvm::Module* Module;
	llvm::Function* printf;
public:
	CodeGenerator(void);
	void PushSymbolTable(void);
	void PopSymbolTable(void);
	void EnterFunction(llvm::Function* Func);
	void LeaveFunction(void);
	llvm::Function* FindFunction(std::string Name);
	bool AddFunction(std::string Name, llvm::Function* Function);
	llvm::Value* FindVariable(std::string Name);
	bool AddVariable(std::string Name, llvm::Value* Variable);
	bool AddConstant(std::string Name, llvm::Value* Constant);
	llvm::Function* GetCurrentFunction(void);
	void EnterLoop(llvm::BasicBlock* ContinueBB, llvm::BasicBlock* BreakBB);
	void LeaveLoop(void);
	llvm::BasicBlock* GetContinueBlock(void);
	llvm::BasicBlock* GetBreakBlock(void);
	void DumpIRCode(std::string FileName);
	void GenObjectCode(std::string FileName);
	llvm::Function* getPrintf();
	void GenerateCode(AST::Program& Root, const std::string& OptimizeLevel) ;
	void XIPBB(void) ;
	llvm::Value* FindConstant(std::string Name) ;
private:
	class Symbol 
	{
	public:
		Symbol(void) : Content(NULL), Type(UNDEFINED) {}
		Symbol(llvm::Function* Func) : Content(Func), Type(FUNCTION) {}
		Symbol(llvm::Type* Ty) : Content(Ty), Type(TYPE) {}
		Symbol(llvm::Value* Value, bool isConst) : Content(Value), Type(isConst ? CONSTANT : VARIABLE) {}
		llvm::Function* GetFunction(void) { return this->Type == FUNCTION ? (llvm::Function*)Content : NULL; }
		llvm::Type* GetType(void) { return this->Type == TYPE ? (llvm::Type*)Content : NULL; }
		llvm::Value* GetVariable(void) { return this->Type == VARIABLE ? (llvm::Value*)Content : NULL; }
		llvm::Value* GetConstant(void) { return this->Type == CONSTANT ? (llvm::Value*)Content : NULL; }
	private:
		void* Content;
		enum 
		{
			FUNCTION,
			TYPE,
			VARIABLE,
			CONSTANT,
			UNDEFINED
		} Type;
	};
	using SymbolTable = std::map<std::string, Symbol>;

private:
	llvm::DataLayout* DL;
	llvm::Function* CurrFunction;
	std::vector<llvm::BasicBlock*> ContinueBlockStack;
	std::vector<llvm::BasicBlock*> BreakBlockStack;	
	std::vector<SymbolTable*> SymbolTableStack;	
	llvm::BasicBlock* TmpBB;
	llvm::Function* TmpFunc;
};





#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
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

class codegenerator;
namespace AST{
    class Node
    {
        public:
        virtual ~Node() = default;
        //virtual Value *codegen() = 0;
    };

    class Stat:public Node
    {
        public:
        virtual llvm::Value *codegen(codegenerator& __generator) = 0;
    };

    class Define_Block: public Stat
    {
        public:
        virtual llvm::Value *codegen(codegenerator& __generator) = 0;
    };

    class Define_List: public Node
    {
        public:
            std::vector<Define_Block*> define_list;
            llvm::Value *codegen(codegenerator& __generator);
            void add_define(Define_Block* __define_block){
                define_list.push_back(__define_block);
            }
    };

    class Program: public Node
    {
        public:
            Define_List* define_list;
            llvm::Value *codegen(codegenerator& __generator);
            Program(Define_List* __define_list){
                define_list = __define_list;
            }
    };

    class Specifier: public Node
    {
        public:
        std::string type;
        Specifier(const std::string& __type){
            type = __type;
        }
        llvm::Type* gettype();
    };

    class Exp: public Stat
    {
        public:
        virtual llvm::Value *codegen(codegenerator& __generator) = 0;
    };

    class Exp_Bin: public Exp
    {
        public:
        std::string bin_op;
        Exp* left;
        Exp* right;
        Exp_Bin(const std::string& __bin_op, Exp* __left, Exp* __right){
            bin_op = __bin_op;
            left = __left;
            right = __right;
        }
        llvm::Value *codegen(codegenerator& __generator) override;
        llvm::Value* codegenPtr(codegenerator& __generator) override {return nullptr;}
    };
    }
    }
}
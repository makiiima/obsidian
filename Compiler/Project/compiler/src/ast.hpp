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
namespace AST
{
    class Node
    {
    public:
        virtual ~Node() = default;
        // virtual Value *codegen() = 0;
    };

    class Stat : public Node
    {
    public:
        virtual llvm::Value *codegen(codegenerator &__generator) = 0;
    };

    class Define_Block : public Stat
    {
    public:
        virtual llvm::Value *codegen(codegenerator &__generator) = 0;
    };

    class Define_List : public Node
    {
    public:
        std::vector<Define_Block *> define_list;
        llvm::Value *codegen(codegenerator &__generator);
        void add_define(Define_Block *__define_block)
        {
            define_list.push_back(__define_block);
        }
    };

    class Program : public Node
    {
    public:
        Define_List *define_list;
        llvm::Value *codegen(codegenerator &__generator);
        Program(Define_List *__define_list)
        {
            define_list = __define_list;
        }
    };

    class Specifier : public Node
    {
    public:
        std::string type;
        Specifier(const std::string &__type)
        {
            type = __type;
        }
        llvm::Type *gettype();
    };

    class Exp : public Stat
    {
    public:
        virtual llvm::Value *codegenPtr(codegenerator &__generator) = 0;
    };

    class Exp_Bin : public Exp
    {
    public:
        std::string bin_op;
        Exp *left;
        Exp *right;
        Exp_Bin(const std::string &__bin_op, Exp *__left, Exp *__right)
        {
            bin_op = __bin_op;
            left = __left;
            right = __right;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Exp_Uni : public Exp
    {
    public:
        std::string uni_op;
        Exp *exp;
        Exp_Uni(const std::string &__uni_op, Exp *__exp)
        {
            uni_op = __uni_op;
            exp = __exp;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Exp_Con : public Exp // a?b:c
    {
    public:
        Exp *cond;
        Exp *left;
        Exp *right;
        Exp_Con(Exp *__cond, Exp *__left, Exp *__right)
        {
            cond = __cond;
            left = __left;
            right = __right;
        }
        llvm::Value *codegen(codegenerator &__generator) override { return nullptr; }
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Exp_List : public Exp
    {
    public:
        std::vector<Exp *> exp_list;
        Exp_List()
        {
            exp_list.clear();
        }
        void add_exp(Exp *__exp)
        {
            exp_list.push_back(__exp);
        }
        llvm::Value *codegen(codegenerator &__generator) override { return nullptr; }
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Exp_Func : public Exp
    {
    public:
        std::string func_name;
        Exp_List *parameters;
        Exp_Func(const std::string &__func_name, Exp_List *__parameters)
        {
            func_name = __func_name;
            parameters = __parameters;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Exp_Assign : public Exp
    {
    public:
        Exp *left, *right;
        Exp_Assign(Exp *__left, Exp *__right)
        {
            left = __left;
            right = __right;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override;
    };

    class Exp_Id : public Exp
    {
    public:
        std::string id;
        Exp_Id(const std::string &__id)
        {
            id = __id;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override;
    };

    class Const : public Exp
    {
    public:
        virtual llvm::Value *codegenPtr(codegenerator &__generator) = 0;
    };

    class Const_Int : public Const
    {
    public:
        int value;
        Const_Int(int __value)
        {
            value = __value;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Const_Char : public Const
    {
    public:
        char value;
        Const_Char(char __value)
        {
            value = __value;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Const_String : public Const
    {
    public:
        std::string value;
        Const_String(const std::string &__value)
        {
            value = __value;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
        llvm::Value *codegenPtr(codegenerator &__generator) override { return nullptr; }
    };

    class Stat_List : public Node
    {
    public:
        std::vector<Stat *> stat_list;
        Stat_List()
        {
            stat_list.clear();
        }
        void add_stat(Stat *__stat)
        {
            stat_list.push_back(__stat);
        }
        llvm::Value *codegen(codegenerator &__generator);
    };

    class Block : public Node
    {
    public:
        Stat_List *stat_list;
        Block(Stat_List *__stat_list)
        {
            stat_list = __stat_list;
        }
        llvm::Value *codegen(codegenerator &__generator);
    };

    class Stat_Exp : public Stat
    {
    public:
        Exp *exp;
        Stat_Exp(Exp *__exp)
        {
            exp = __exp;
        }
    };

    class Stat_Return : public Stat
    {
    public:
        Exp *exp;
        Stat_Return(Exp *__exp)
        {
            exp = __exp;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Stat_If : public Stat
    {
    public:
        Exp *exp;
        Block *block;
        Stat_If(Exp *__exp, Block *__block)
        {
            exp = __exp;
            block = __block;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Stat_IfElse : public Stat
    {
    public:
        Exp *exp;
        Block *block1, *block2;
        Stat_IfElse(Exp *__exp, Block *__block1, Block *__block2)
        {
            exp = __exp;
            block1 = __block1;
            block2 = __block2;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Stat_For : public Stat
    {
    public:
        Exp *exp1, *exp2, *exp3;
        Block *block;
        Stat_For(Exp *__exp1, Exp *__exp2, Exp *__exp3, Block *__block)
        {
            exp1 = __exp1;
            exp2 = __exp2;
            exp3 = __exp3;
            block = __block;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Stat_While : public Stat
    {
    public:
        Exp *exp;
        Block *block;
        Stat_While(Exp *__exp, Block *__block)
        {
            exp = __exp;
            block = __block;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Stat_DoWhile : public Stat
    {
    public:
        Exp *exp;
        Block *block;
        Stat_DoWhile(Exp *__exp, Block *__block)
        {
            exp = __exp;
            block = __block;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Var_Dec : public Define_Block
    {
    public:
        std::string type;
        std::string id;
        Exp *exp;
        Var_Dec(const std::string &__type, const std::string &__id, Exp *__exp)
        {
            type = __type;
            id = __id;
            exp = __exp;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Para_List : public Node
    {
    public:
        std::vector<Var_Dec *> para_list;
        Para_List()
        {
            para_list.clear();
        }
        void add_para(Var_Dec *__para)
        {
            para_list.push_back(__para);
        }
    };

    class Fun_Imp : public Define_Block
    {
    public:
        std::string type;
        std::string id;
        Para_List *parameters;
        Block *block;
        Fun_Imp(const std::string &__type, const std::string &__id, Para_List *__parameters, Block *__block)
        {
            type = __type;
            id = __id;
            parameters = __parameters;
            block = __block;
        }
        llvm::Value *codegen(codegenerator &__generator) override;
    };

    class Var_Init : public Node
    {
    public:
        Exp_Id *id;
        Exp *exp;
        Var_Init(Exp_Id *__id, Exp *__exp)
        {
            id = __id;
            exp = __exp;
        }
    };

    class Var_List : public Node
    {
    public:
        std::vector<Var_Init *> var_list;
        Var_List()
        {
            var_list.clear();
        }
        void add_var(Var_Init *__var)
        {
            var_list.push_back(__var);
        }
    };
}

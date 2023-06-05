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

class CodeGenerator;
namespace AST{
    class Node 
    {
    public:
        virtual ~Node() = default;
        //virtual Value *codegen() = 0;
        void visualization(int n){return;}
    };

    class Stat: public Node
    {
    // Value *codegen() override;
    public:
        virtual void visualization(int n)=0;
        virtual llvm::Value *codegen(CodeGenerator& __Generator) = 0;
    };

    class Define_Block: public Stat
    {
    public:
        virtual llvm::Value *codegen(CodeGenerator& __Generator) = 0;
        virtual void visualization(int n)=0;
    };

    class Define_List: public Node
    {
    public:
        std::vector<Define_Block*> DefineList_ ;
        //DefineList(std::vector<Define_Block*> DefineList_):DefineList_(DefineList_){}
        llvm::Value *codegen(CodeGenerator& __Generator) ;
        void adddefine(Define_Block* a){DefineList_.push_back(a);}
        void visualization(int n);
    };

    class Program : public Node
    {
    public:
        Define_List* Define_List_;
        llvm::Value *codegen(CodeGenerator& __Generator) ;
        Program(Define_List* Define_List_): Define_List_(Define_List_) {}
        void visualization(int n, std::string file_path);
    };

    class Specifier : public Node 
    {
    public:    
        std::string type;
        Specifier(const std::string& type) : type(type) {}
        llvm::Type*getType() ;
        void visualization(int n);
    };



    class Exp : public Stat
    {
    public:
        virtual llvm::Value* CodeGenPtr(CodeGenerator& __Generator) = 0;
    };

    /*
                    Exp ADD Exp
                    | Exp SUB Exp
                    | Exp MUL_PTR Exp
                    | Exp DIV Exp
                    | Exp MOD Exp
                    | Exp BITAND_ADDRESS Exp
                    | Exp AND Exp
                    | Exp OR Exp
                    | Exp BITOR Exp
                    | Exp XOR Exp
                    | Exp LSHIFT Exp
                    | Exp RSHIFT Exp
                    | Exp ADDEQ Exp
                    | Exp SUDEQ Exp
                    | Exp MULEQ Exp
                    | Exp DIVEQ Exp
                    | Exp MODEQ Exp
                    | Exp BITANDEQ Exp
                    | Exp BITOREQ Exp
                    | Exp BITXOR Exp
                    | Exp LSHIFTEQ Exp
                    | Exp RSHIFTEQ Exp
    */
    class Exp_Bin : public Exp
    {
    public:
        std::string bin_operation;
        Exp *a,*b;
        Exp_Bin(std::string bin_operation,Exp *a,Exp *b): bin_operation(bin_operation),a(a),b(b) {}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
        void visualization(int n);
    };

    class Exp_Uni : public Exp
    {
    public:
        std::string uni_operation;
        Exp *a;
        Exp_Uni(std::string uni_operation,Exp* a): uni_operation(uni_operation),a(a) {}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;};
        void visualization(int n);
    };

    class Exp_Con : public Exp // a?b :c
    {
    public:
        Exp *a,*b,*c;
        Exp_Con(Exp *a,Exp *b,Exp* c): a(a),b(b),c(c) {}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override {return NULL;}
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
    };

    class Exp_List : public Exp
    {
    public:
        std::vector<Exp*> Exp_List_ ;
        //Exp_List(std::vector<Exp*> Exp_List_):Exp_List_(Exp_List_){}
        void addexp(Exp* a){Exp_List_.push_back(a);}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override {return NULL;}
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
    };

    class Exp_Func : public Exp
    {
    public:
        std::string Func_Name;
        Exp_List* Parameters;
        Exp_Func(std::string Func_Name,Exp_List* Parameters):Func_Name(Func_Name),Parameters(Parameters){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override ;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
    };

    class Exp_Comma : public Exp
    {
    public:
        Exp *a, *b;
        Exp_Comma(Exp *a, Exp* b):a(a),b(b) {}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
    };

    class Exp_Assign : public Exp
    {
    public:
        Exp *a, *b;
        Exp_Assign(Exp *a, Exp *b):a(a),b(b) {}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
        
    };

    class Exp_ID : public Exp
    {
    public:
        std::string ID_Name;
        Exp_ID(std::string ID_Name):ID_Name(ID_Name){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override;
    };

    class Constant : public Exp
    {
    public:
        virtual llvm::Value *codegen(CodeGenerator& __Generator) = 0;
        llvm::Value* CodeGenPtr(CodeGenerator& __Generator)override{return NULL;}
    };

    class Constant_Int : public Constant
    {
    public:
        int Val;
        Constant_Int(int Val):Val(Val){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };

    class Constant_Double : public Constant
    {
    public:
        double Val;
        Constant_Double(double Val):Val(Val){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };

    class Constant_Bool : public Constant
    {
    public:
        bool Val;
        Constant_Bool(bool Val):Val(Val){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };

    class Constant_Char : public Constant
    {
    public:
        char Val;
        Constant_Char(char Val):Val(Val){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };

    class Constant_String : public Constant
    {
    public:
        std::string Val;
        Constant_String(std::string Val):Val(Val){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };



    class Stat_List : public Node
    {
    public:
        std::vector<Stat*> Stat_List_ ;
        //StatList(std::vector<Stat*> StatList_):StatList_(StatList_){}
    // Value *codegen(CodeGenerator& __Generator) override;
    void addstat(Stat* a){Stat_List_.push_back(a);}
    void visualization(int n);
    };

    class Block : public Node
    {
    public:
        Stat_List* StatList_;
        Block(Stat_List* StatList_): StatList_( StatList_){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) ;
    };

    class Stat_Exp : public Stat
    {
    public:
        Exp *a;
        Stat_Exp(Exp *a): a(a){}
        void visualization(int n);
        
    };

    class Stat_Return : public Stat
    {
    public:
        Exp* a;
        Stat_Return(Exp *a): a(a){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override ;
    
    };

    class Stat_If : public Stat
    {
    public:
        Exp *a;
        Block *t;
        Stat_If(Exp *a,Block *t): a(a),t(t){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override;
    };

    class Stat_IfElse : public Stat
    {
    public:
        Exp *a;
        Block *t,*f;
        Stat_IfElse(Exp *a,Block *t,Block *f): a(a),t(t),f(f){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override;
    
    };

    class Stat_For : public Stat
    {
    public:
        Exp *a,*b,*c;
        Block *t;
        Stat_For(Exp *a,Exp* b,Exp *c,Block *t): a(a),b(b),c(c),t(t){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override;
    
    };

    class Stat_While : public Stat
    {
    public:
        Exp *a;
        Block *t;
        Stat_While(Exp* a,Block* t): a(a),t(t){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override ;
    
    };

    class Stat_DoWhile : public Stat
    {
    public:
        Exp *a;
        Block *t;
        Stat_DoWhile(Exp *a,Block *t): a(a),t(t){}
        void visualization(int n);
        llvm::Value *codegen(CodeGenerator& __Generator) override ;
    
    };



    class Var_Dec: public Define_Block
    {
    public:
        Specifier *Type;
        std::string ID;
        Var_Dec(Specifier *Type,std::string ID):Type(Type),ID(ID){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };

    class Para_List : public Node
    {
    public:
        std::vector<Specifier*> Specifier_List_ ;
        std::vector<std::string> Exp_ID_List_ ;
        Para_List(){}
        void addpara(Specifier* Specifier ,std::string Exp){Specifier_List_.push_back(Specifier);Exp_ID_List_.push_back(Exp);}
        void visualization(int n);
    };

    class Fun_Imp: public Define_Block
    {
    public:
        Specifier *Return_Type;
        std::string Fun_ID;
        Para_List *ParaList_;
        Block * Fun_Block;
        Fun_Imp(Specifier *Return_Type,std::string Fun_ID,Para_List *ParaList_,Block  *Fun_Block):Return_Type(Return_Type),ParaList_(ParaList_),Fun_ID(Fun_ID),Fun_Block(Fun_Block){}
        Fun_Imp(Specifier *Return_Type,std::string Fun_ID,Block  *Fun_Block):Return_Type(Return_Type),ParaList_(NULL),Fun_ID(Fun_ID),Fun_Block(Fun_Block){}
        llvm::Value *codegen(CodeGenerator& __Generator) override;
        void visualization(int n);
    };

    class Var_Init : public Node
    {
    public:
        Exp_ID* ID ;
        Exp* Val;
        Var_Init(Exp_ID* ID):ID(ID),Val(NULL){}
        Var_Init(Exp_ID* ID,Exp* Val):ID(ID),Val(Val){}
        void visualization(int n);
    };

    class Var_List : public Node
    {
    public:
        std::vector<Var_Init*> Var_Init_List_ ;
        //VarList(std::vector<Var_Init*> Var_Init_List):Var_Init_List(Var_Init_List){}
        void addvar(Var_Init* a){Var_Init_List_.push_back(a);}
        void visualization(int n);
    };

    
}


// 






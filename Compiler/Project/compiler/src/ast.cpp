#include"ast.hpp"
#include"codegen.hpp"
#include"codegen_helper.hpp"

void Printf_Codegen(codegenerator& __generator)
{
    return;
}

//error
llvm::Value *LogErrorV(const char *Str)
{
    return nullptr;
}

//32bit
llvm::Value *AST::Const_Int::codegen(codegenerator& __generator)
{
    return IRBuilder.getInt32(this->value);
}

//char
llvm::Value *AST::Const_Char::codegen(codegenerator& __generator)
{
    return IRBuilder.getInt8((unsigned char)(this->value));
}

//string
llvm::Value *AST::Const_String::codegen(codegenerator& __generator)
{
    return IRBuilder.CreateGlobalStringPtr(this->value);
}

//return type
llvm::Type *AST::Specifier::gettype()
{
    static llvm::Type* t;
    if(type=="INT")
        t=IRBuilder.getInt32Ty();
    else if(type=="CHAR")
        t=IRBuilder.getInt8Ty();
    else if(type=="VOID")
        t=IRBuilder.getVoidTy();
    else if(type=="STRING")
        {
            llvm::Type *charType = IRBuilder.getInt8Ty();
            t=llvm::PointerType::getUnqual(charType);
        }
    else
        LogErrorV("unknown type");
    return t;
}

//binary expression
llvm::Value *AST::Exp_Bin::codegen(codegenerator& __gen)
{
    llvm::Value *L = this->left->codegen(__gen);
    llvm::Value *R = this->right->codegen(__gen);
    if (!L || !R)
        {
            LogErrorV("lack of operand");
            return nullptr;
        }
    llvm::Type *TL = L->getType();
    llvm::Type *TR = R->getType();
    if(!((TL->isIntegerTy(32) && TR->isIntegerTy(32)) ||
        (TL->isIntegerTy(1) && TR->isIntegerTy(1))))
        {
            LogErrorV("operand type error");
            return nullptr;
        }
    llvm::Type *thistype=TL;
    if(!thistype)
    {
        LogErrorV("unknown type");
        return nullptr;
    }
    
    if(bin_op=="ADD")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateAdd(L,R);
        else{
            LogErrorV("unsupported type bool for ADD operation");
            return nullptr;
        }

    else if(bin_op="SUB")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateSub(L,R);
        else{
            LogErrorV("unsupported type bool for SUB operation");
            return nullptr;
        }
    }
    else if(bin_op="MUL")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateMul(L,R);
        else{
            LogErrorV("unsupported type bool for MUL operation");
            return nullptr;
        }
    }
    else if(bin_op="DIV")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateSDiv(L,R);
        else{
            LogErrorV("unsupported type bool for DIV operation");
            return nullptr;
        }
    }
    else if(bin_op="MOD")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateSRem(L,R);
        else{
            LogErrorV("unsupported type bool for MOD operation");
            return nullptr;
        }
    }
    else if(bin_op="AND")
    {
        if(thistype->isIntegerTy(1))
            return IRBuilder.CreateAnd(L,R);
        else{
            LogErrorV("unsupported type int for AND operation");
            return nullptr;
        }
    }
    else if(bin_op="OR")
    {
        if(thistype->isIntegerTy(1))
            return IRBuilder.CreateOr(L,R);
        else{
            LogErrorV("unsupported type int for OR operation");
            return nullptr;
        }
    }
    else if(bin_op="XOR")
    {
        if(thistype->isIntegerTy(1))
            return IRBuilder.CreateXor(L,R);
        else{
            LogErrorV("unsupported type int for XOR operation");
            return nullptr;
        }
    }
    else if(bin_op="EQ")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateICmpEQ(L,R);
        else if(thistype->isIntegerTy(1))
            return IRBuilder.CreateICmpEQ(L,R);
        else{
            LogErrorV("unsupported type for EQ operation");
            return nullptr;
        }
    }
    else if(bin_op="NE")
    {
        if(thistype->isIntegerTy(32))
            return IRBuilder.CreateICmpNE(L,R);
        else if(thistype->isIntegerTy(1))
        

}
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include "CodeGeneration.hpp"


llvm::Value* Cast2I1(llvm::Value* Value) 
{
	if (Value->getType() == IRBuilder.getInt1Ty())
		return Value;
	else if (Value->getType()->isIntegerTy())
		return IRBuilder.CreateICmpNE(Value, llvm::ConstantInt::get((llvm::IntegerType*)Value->getType(), 0, true));
	else if (Value->getType()->isFloatingPointTy())
		return IRBuilder.CreateFCmpONE(Value, llvm::ConstantFP::get(Value->getType(), 0.0));
	else if (Value->getType()->isPointerTy())
		return IRBuilder.CreateICmpNE(IRBuilder.CreatePtrToInt(Value, IRBuilder.getInt64Ty()), IRBuilder.getInt64(0));
	else 
	{
		throw std::logic_error("Cannot cast to bool type.");
		return NULL;
	}
}



llvm::AllocaInst* CreateEntryBlockAlloca(llvm::Function* Func, std::string VarName, llvm::Type* VarType) 
{
	llvm::IRBuilder<> TmpB(&Func->getEntryBlock(), Func->getEntryBlock().begin());
	return TmpB.CreateAlloca(VarType, 0, VarName);
}


llvm::BranchInst* TerminateBlockByBr(llvm::BasicBlock* BB) 
{
	//If not terminated, jump to the target block
	if (!IRBuilder.GetInsertBlock()->getTerminator())
		return IRBuilder.CreateBr(BB);
	else
		return NULL;
}



llvm::Value* CreateLoad(llvm::Value* pLHS, CodeGenerator& Generator) 
{
	//For array types, return the pointer to its first element
	if (pLHS->getType()->getNonOpaquePointerElementType()->isArrayTy())
		return IRBuilder.CreatePointerCast(pLHS, pLHS->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());
	else
		return IRBuilder.CreateLoad(pLHS->getType()->getNonOpaquePointerElementType(), pLHS);
}

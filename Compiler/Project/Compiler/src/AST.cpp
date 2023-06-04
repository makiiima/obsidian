#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include "AST.hpp"
#include "CodeGeneration.hpp"
#include "Codegen_helper.hpp"


void Printf_Codegen(CodeGenerator& __Generator)
{
  return;
}

// Error
llvm::Value *LogErrorV(const char *Str) 
{
  //std::cout<<Str;
  return NULL;
}

//32bit
llvm::Value* AST::Constant_Int :: codegen(CodeGenerator& __Generator)
{
  return IRBuilder.getInt32(this->Val);
}

//double
llvm::Value* AST::Constant_Double :: codegen(CodeGenerator& __Generator)
{
  return llvm::ConstantFP::get(IRBuilder.getDoubleTy(),this->Val);
}

//bool(int)
llvm::Value* AST::Constant_Bool :: codegen(CodeGenerator& __Generator)
{
  return IRBuilder.getInt1(this->Val);
}


//char
llvm::Value* AST::Constant_Char :: codegen(CodeGenerator& __Generator)
{
  return IRBuilder.getInt8((unsigned char)(this->Val));;
}

//string
llvm::Value* AST::Constant_String :: codegen(CodeGenerator& __Generator)
{

//     在上述示例中，我们使用CreateGlobalString函数创建一个局部字符串常量。
//   函数的第一个参数是字符串的内容，第二个参数是字符串的名称（可选）。该函
//   数会为字符串分配内存，并返回一个Constant指针，指向字符串的首地址。
//     请注意，虽然函数名为CreateGlobalString，但它实际上创建的是一个局部
//   字符串，而非全局常量。函数名中的"Global"仅表示字符串的内容是全局可见的。
//     您可以将获取到的字符串常量用于后续的IR指令生成或其他操作。如果要在不同
//   的基本块（basic block）中使用该字符串，需要注意在正确的基本块中加载
//   （Load）该指针。
//   
  llvm::Value* v=IRBuilder.CreateGlobalStringPtr(this->Val);
  return v;
  //return IRBuilder.CreateGlobalStringPtr(this->Val);
}

//return the type
llvm::Type* AST::Specifier :: getType()
{
  static llvm::Type* t;
  if(type=="INT")
    t= IRBuilder.getInt32Ty();
  else if(type=="BOOL")
    t= IRBuilder.getInt1Ty();
  else if(type=="DOUBLE")
    t= IRBuilder.getDoubleTy();
  else if(type=="CHAR")
    t= IRBuilder.getInt8Ty();
  else if(type=="STRING")
  {
    llvm::Type *charType = IRBuilder.getInt8Ty();
    t=  llvm::PointerType::getUnqual(charType);
  }
  else if(type=="VOID")
    t=IRBuilder.getVoidTy();
  else
    LogErrorV("Unknown type ");
  return t;
}


//a+b, a-b, ..
llvm::Value *AST::Exp_Bin::codegen(CodeGenerator& __Generator) 
{

  llvm::Value *L = a->codegen(__Generator);
  llvm::Value *R = b->codegen(__Generator);
  if (!L || !R)
  {
    LogErrorV("lack of oprations");
    return nullptr;
  }
  llvm::Type* TL=L->getType();
  llvm::Type* TR=R->getType();
  if(!((TL->isIntegerTy(32)&&TR->isIntegerTy(32))||(TL->isDoubleTy()&&TR->isDoubleTy())||(TL->isIntegerTy(1)&&TR->isIntegerTy(1))))
  {
    std::cout<<"exp_bin opration type wrong\n";
    return NULL;
  }
  llvm::Type* thistype=TL;
  if(!thistype)
  {
    LogErrorV("operation type error");
    return nullptr;  
  }
  if(bin_operation=="ADD")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateAdd(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFAdd(L, R);
    else 
      LogErrorV("ADD operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="SUB")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateSub(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFSub(L, R);
    else 
      LogErrorV("SUB operation type does't support bool");
      return nullptr;    
  }
  else if(bin_operation=="MUL")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateMul(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFMul(L, R);
    else 
      LogErrorV("MUL operation type does't support bool");
      return nullptr;    
  }
  else if(bin_operation=="DIV")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateSDiv(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFDiv(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="MOD")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateSRem(L, R);
    else
      LogErrorV("MOD operation type does't support double or bool");
      return nullptr;
  }
  else if(bin_operation=="BINAND_ADDRESS")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateAnd(L, R);
    else
      LogErrorV("BINAND_ADDRESS operation type does't support double or bool");
      return nullptr; 

  }   
  else if(bin_operation=="BITOR")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateOr(L, R);
    else
      LogErrorV("BITOR operation type does't support double or bool");
      return nullptr; 

  }
  else if(bin_operation=="XOR")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateXor(L, R);
    else
      LogErrorV("XOR operation type does't support double or bool");
      return nullptr; 

  }
  else if(bin_operation=="AND")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateXor(L, R);
    else
      LogErrorV("XOR operation type does't support double or bool");
      return nullptr;  

  } 
  else if(bin_operation=="GT")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateICmpSGT(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFCmpOGT(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="GEQ")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateICmpSGE(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFCmpOGE(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="LT")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateICmpSLT(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFCmpOLT(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="LEQ")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateICmpSLE(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFCmpOLE(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="EQ")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateICmpEQ(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFCmpOEQ(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else if(bin_operation=="NEQ")
  {
    if(thistype->isIntegerTy(32))
      return IRBuilder.CreateICmpNE(L, R);
    else if (thistype->isDoubleTy())
      return IRBuilder.CreateFCmpONE(L, R);
    else 
      LogErrorV("DIV operation type does't support bool");
      return nullptr;
  }
  else
    return LogErrorV("invalid binary operator");
  
}

//var declartion
llvm::Value* AST::Var_Dec::codegen(CodeGenerator& __Generator)
{
  llvm::Type* Var_Type;
  Var_Type=Type->getType();
  
  if(!__Generator.GetCurrentFunction())
  {
    llvm::Constant* Initializer = NULL;
		if(1) 
    {
			__Generator.XIPBB();
			llvm::Value* InitialExpr = IRBuilder.getInt32(10);
      if (InitialExpr == NULL) 
      {
				throw std::logic_error("Initializing variable " + ID+ " with value of different type.");
				return NULL;
			}
		  __Generator.XIPBB();
			Initializer = (llvm::Constant*)InitialExpr;
		}
  //else Initializer = llvm::UndefValue::get(Var_Type);
	auto Alloc = new llvm::GlobalVariable(
		*(__Generator.Module),
		Var_Type,
		false,
		llvm::Function::ExternalLinkage,
		Initializer,
		ID
		);
	if(!__Generator.AddVariable(ID, Alloc)) 
  {
		throw std::logic_error("Redefining global variable " + ID+ ".");
		Alloc->eraseFromParent();
		return NULL;
	}		
  }
  else
  {
				auto Alloc = CreateEntryBlockAlloca(__Generator.GetCurrentFunction(), ID, Var_Type);
				if (!__Generator.AddVariable(ID, Alloc)) 
        {
					throw std::logic_error("Redefining local variable " + ID + ".");
					Alloc->eraseFromParent();
					return NULL;
				}
  }
  return NULL;
}

//llvm:Value* AST::Define_List::codegen(CodeGenerator& __Codegenerator)

// llvm::Value* AST::Define_List::codegen(CodeGenerator& __Generator)
// {
//   Var_Dec* p;
//   for (unsigned i = 0, e = DefineList_.size(); i != e; ++i)
//   {
//     DefineList_[i]->codegen();
//   }
// }

llvm::Value* AST::Fun_Imp::codegen(CodeGenerator& __Generator) 
{
  std::vector<llvm::Type*> ArgTypes;
		bool ContainVoidTy = true;
    //if not void
    if(ParaList_)
    {
      ContainVoidTy=false;
		  for (auto iter=(ParaList_->Specifier_List_).begin();iter!=(ParaList_->Specifier_List_).end();iter++) 
      {
			  llvm::Type* LLVMType =(*iter)->getType();
			  ArgTypes.push_back(LLVMType);
		  }
    }
		if (ContainVoidTy) ArgTypes.clear();
		llvm::Type* RetTy = Return_Type->getType();
		llvm::FunctionType* FuncType = llvm::FunctionType::get(RetTy, ArgTypes, false);
		llvm::Function* Func = llvm::Function::Create(FuncType, llvm::GlobalValue::ExternalLinkage, Fun_ID, __Generator.Module);
		__Generator.AddFunction(Fun_ID, Func);

		llvm::BasicBlock* FuncBlock = llvm::BasicBlock::Create(Context, "entry", Func);
		IRBuilder.SetInsertPoint(FuncBlock);
		__Generator.PushSymbolTable();	
		size_t Index = 0;
		for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++, ++Index) 
    {
			auto Alloc = CreateEntryBlockAlloca(Func,(ParaList_->Exp_ID_List_)[Index] , ArgTypes[Index]);
			IRBuilder.CreateStore(ArgIter, Alloc);
			__Generator.AddVariable((ParaList_->Exp_ID_List_)[Index], Alloc);
		}
			__Generator.EnterFunction(Func);
			__Generator.PushSymbolTable();
			Fun_Block->codegen(__Generator);
			__Generator.PopSymbolTable();
			__Generator.LeaveFunction();
			__Generator.PopSymbolTable();
		
		return NULL;
}

llvm::Value* AST::Block::codegen(CodeGenerator& __Generator)
{
  __Generator.PushSymbolTable();
  for (auto iter=(StatList_->Stat_List_).begin();iter!=(StatList_->Stat_List_).end(); ++iter)
			if (IRBuilder.GetInsertBlock()->getTerminator())
				break;
			else
				(*iter)->codegen(__Generator);
    __Generator.PopSymbolTable();
		return NULL;
}


llvm::Value* AST::Exp_Assign::codegen(CodeGenerator& __Generator)
{
  llvm::Value* PL = a->CodeGenPtr(__Generator);
  llvm::Value* R=b->codegen(__Generator);

  PL = IRBuilder.CreateStore(R,PL);
  return  NULL;
}

//i++, ++i ..
llvm::Value* AST::Exp_Uni::codegen(CodeGenerator& __Generator)
{
  llvm::Value *curr = a->codegen(__Generator);
  if (!curr)
  {
    LogErrorV("lack of oprations");
    return nullptr;
  }
  llvm::Type* Tcurr=curr->getType();
  if(!(Tcurr->isIntegerTy(32)) && !(Tcurr->isDoubleTy()))
  {
    std::cout<<"exp_uni opration type wrong\n";
    return NULL;
  }
  llvm::Type* thistype=Tcurr;
  if(!thistype)
  {
    LogErrorV("operation type error");
    return nullptr;  
  }
  llvm::Value* constValue1 = IRBuilder.getInt32(1);
  llvm::Value* constValue0 = IRBuilder.getInt32(0);
  if(uni_operation=="POSTFIX_INC")//i++
  {
    if(thistype->isIntegerTy(32))
    {
      llvm::Value* addInst = IRBuilder.CreateAdd(curr, constValue1);
      llvm::Value* PL = a->CodeGenPtr(__Generator);
      PL=IRBuilder.CreateStore(addInst,PL);
      return curr;
    }
    //else if (thistype->isDoubleTy())
      //return IRBuilder.CreateFAdd(curr, constValue);
    else 
      LogErrorV("INC operation type does't support bool or double");
      return nullptr;
  }
  else if(uni_operation == "POSFIX_DEC")//i--
  {
    if(thistype->isIntegerTy(32))
    {
      
      llvm::Value* subInst = IRBuilder.CreateSub(curr, constValue1);
      llvm::Value* PL = a->CodeGenPtr(__Generator);
      PL=IRBuilder.CreateStore(subInst,PL);
      return curr;
    }
   // else if (thistype->isDoubleTy())
      //return IRBuilder.CreateFSub(curr, constValue);
    else 
      LogErrorV("DEC operation type does't support bool or double");
      return nullptr;    
  }
  else if(uni_operation == "PREFIX_INC")//++i
  {
    if(thistype->isIntegerTy(32))
    {
      llvm::Value* addInst = IRBuilder.CreateAdd(curr, constValue1);
      llvm::Value* PL = a->CodeGenPtr(__Generator);
      PL=IRBuilder.CreateStore(addInst,PL);
      return addInst;
    }
    //else if (thistype->isDoubleTy())
      //return IRBuilder.CreateFAdd(curr, constValue);
    else 
      LogErrorV("INC operation type does't support bool or double");
      return nullptr;
  }
  else if(uni_operation == "PREFIX_INC")//--i
  {
    if(thistype->isIntegerTy(32))
    {
      
      llvm::Value* subInst = IRBuilder.CreateSub(curr, constValue1);
      llvm::Value* PL = a->CodeGenPtr(__Generator);
      PL=IRBuilder.CreateStore(subInst,PL);
      return subInst;
    }
   // else if (thistype->isDoubleTy())
      //return IRBuilder.CreateFSub(curr, constValue);
    else 
      LogErrorV("DEC operation type does't support bool or double");
      return nullptr;    
  }
  else
    return LogErrorV("invalid uniexp");
  return NULL;
};


llvm::Value* AST::Exp_ID::codegen(CodeGenerator& __Generator)
{
  llvm::Value* VarPtr = __Generator.FindVariable(ID_Name);
		if (VarPtr) return CreateLoad(VarPtr, __Generator);
		VarPtr = __Generator.FindConstant(ID_Name);
		if (VarPtr) return VarPtr;
		return NULL;
};

llvm::Value* AST::Program::codegen(CodeGenerator& __Generator)
{
    Printf_Codegen(__Generator);
    auto m=Define_List_->DefineList_;
    Define_List_->codegen( __Generator);
    return NULL;
}

llvm::Value* AST::Stat_Return::codegen(CodeGenerator& __Generator)
{
    IRBuilder.CreateRet(a->codegen(__Generator));
    return NULL;
}


llvm::Value* AST::Exp_Func::codegen(CodeGenerator& __Generator)
{		
  if(Func_Name == "printf")
  {
    std::vector<llvm::Value *> *printf_args = new std::vector<llvm::Value *>;
    for(auto it: Parameters->Exp_List_)
    {
      llvm::Value* tmp = it->codegen(__Generator);
      printf_args->push_back(tmp);
    }
    return IRBuilder.CreateCall(__Generator.printf, *printf_args, "printf");
  }
  llvm::Function* Func = __Generator.FindFunction(Func_Name);
	if(Func == NULL) 
  {
		std::cout<<"undefined function: "<<Func_Name<<"\n";
		return NULL;
	}
	std::vector<llvm::Value*> ArgList;
	size_t Index = 0;
	for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ++ArgIter, ++Index) 
    {
			llvm::Value* Arg = Parameters->Exp_List_ .at(Index)->codegen(__Generator);
			if (Arg == NULL) 
      {
				throw std::invalid_argument(std::to_string(Index) + "-th arg type doesn't match when calling function " + this->Func_Name + ".");
				return NULL;
			}
			ArgList.push_back(Arg);
		}
		if (Func->isVarArg())
			for (; Index < Parameters->Exp_List_ .size(); Index++) 
      {
				llvm::Value* Arg = Parameters->Exp_List_ .at(Index)->codegen(__Generator);
				ArgList.push_back(Arg);
			}
		return IRBuilder.CreateCall(Func, ArgList);
}

llvm::Value* AST::Define_List::codegen(CodeGenerator& __Generator)
{
    
    for (auto iter = DefineList_.begin(); iter != DefineList_.end(); iter++)
	{
        llvm::Value* t=(*iter)->codegen(__Generator);
    }
    return NULL;
}

llvm::Value* AST::Exp_Comma::codegen(CodeGenerator& __Generator)
{
    a->codegen(__Generator);
    return b->codegen(__Generator);
}

llvm::Value* AST::Stat_If::codegen(CodeGenerator& __Generator)
{
  llvm::Value* Condition = this->a->codegen(__Generator);
	
	return NULL;
}

llvm::Value* AST::Stat_IfElse::codegen(CodeGenerator& __Generator)
{
  llvm::Value* Condition = this->a->codegen(__Generator);
	if (!(Condition = Cast2I1(Condition))) 
  {
		throw std::logic_error("The condition value of if-statement must be either an integer, or a floating-point number, or a pointer.");
		return NULL;
	}
	llvm::Function* CurrentFunc = __Generator.GetCurrentFunction();
	llvm::BasicBlock* ThenBB = llvm::BasicBlock::Create(Context, "Then");
	llvm::BasicBlock* ElseBB = llvm::BasicBlock::Create(Context, "Else");
	llvm::BasicBlock* MergeBB = llvm::BasicBlock::Create(Context, "Merge");

  //condtional branch
	IRBuilder.CreateCondBr(Condition, ThenBB, ElseBB);
	CurrentFunc->getBasicBlockList().push_back(ThenBB);

	IRBuilder.SetInsertPoint(ThenBB);
	if (this->t) 
  {
		__Generator.PushSymbolTable();
		this->t->codegen(__Generator);
		__Generator.PopSymbolTable();
	}
	TerminateBlockByBr(MergeBB);
	CurrentFunc->getBasicBlockList().push_back(ElseBB);

	IRBuilder.SetInsertPoint(ElseBB);
	if (this->f) 
  {
		__Generator.PushSymbolTable();
		this->f->codegen(__Generator);
		__Generator.PopSymbolTable();
	}

	TerminateBlockByBr(MergeBB);
	if (MergeBB->hasNPredecessorsOrMore(1)) 
  {
		CurrentFunc->getBasicBlockList().push_back(MergeBB);
		IRBuilder.SetInsertPoint(MergeBB);
	}
	return NULL;
}

llvm::Value* AST::Stat_While::codegen(CodeGenerator& __Generator)
{
  llvm::Function* CurrentFunc = __Generator.GetCurrentFunction();
	llvm::BasicBlock* WhileCondBB = llvm::BasicBlock::Create(Context, "WhileCond");
	llvm::BasicBlock* WhileLoopBB = llvm::BasicBlock::Create(Context, "WhileLoop");
	llvm::BasicBlock* WhileEndBB = llvm::BasicBlock::Create(Context, "WhileEnd");
	IRBuilder.CreateBr(WhileCondBB);
	
  //cond
	CurrentFunc->getBasicBlockList().push_back(WhileCondBB);
	IRBuilder.SetInsertPoint(WhileCondBB);
	llvm::Value* Condition = this->a->codegen(__Generator);
	if (!(Condition = Cast2I1(Condition))) 
  {
		throw std::logic_error("The condition value of while-statement is wrong.");
		return NULL;
	}

	IRBuilder.CreateCondBr(Condition, WhileLoopBB, WhileEndBB);

  //lp
	CurrentFunc->getBasicBlockList().push_back(WhileLoopBB);
	IRBuilder.SetInsertPoint(WhileLoopBB);
	if(this->t) 
  {
		__Generator.EnterLoop(WhileCondBB, WhileEndBB);	//Don't forget to call "EnterLoop"
		__Generator.PushSymbolTable();
		this->t->codegen(__Generator);
		__Generator.PopSymbolTable();
		__Generator.LeaveLoop();						//Don't forget to call "LeaveLoop"
	}
	TerminateBlockByBr(WhileCondBB);

	//end
	CurrentFunc->getBasicBlockList().push_back(WhileEndBB);
	IRBuilder.SetInsertPoint(WhileEndBB);
	return NULL;
}

llvm::Value* AST::Stat_DoWhile::codegen(CodeGenerator& __Generator)
{
  llvm::Function* CurrentFunc = __Generator.GetCurrentFunction();
	llvm::BasicBlock* DoLoopBB = llvm::BasicBlock::Create(Context, "DoLoop");
	llvm::BasicBlock* DoCondBB = llvm::BasicBlock::Create(Context, "DoCond");
	llvm::BasicBlock* DoEndBB = llvm::BasicBlock::Create(Context, "DoEnd");
	
  //doloop
	IRBuilder.CreateBr(DoLoopBB);
	CurrentFunc->getBasicBlockList().push_back(DoLoopBB);
	IRBuilder.SetInsertPoint(DoLoopBB);

	if (this->t) 
  {
		__Generator.EnterLoop(DoCondBB, DoEndBB);	
		__Generator.PushSymbolTable();
		this->t->codegen(__Generator);
		__Generator.PopSymbolTable();
		__Generator.LeaveLoop();					
		}
		TerminateBlockByBr(DoCondBB);

  //cond
	CurrentFunc->getBasicBlockList().push_back(DoCondBB);
	IRBuilder.SetInsertPoint(DoCondBB);
	llvm::Value* Condition = this->a->codegen(__Generator);
	if(!(Condition = Cast2I1(Condition))) 
  {
		throw std::logic_error("The condition value of dowhile-statement is wrong.");
		return NULL;
	}
	IRBuilder.CreateCondBr(Condition, DoLoopBB, DoEndBB);
		
  //end
	CurrentFunc->getBasicBlockList().push_back(DoEndBB);
	IRBuilder.SetInsertPoint(DoEndBB);
	return NULL;
}

llvm::Value* AST::Stat_For::codegen(CodeGenerator& __Generator)
{
  llvm::Function* CurrentFunc = __Generator.GetCurrentFunction();
	llvm::BasicBlock* ForCondBB = llvm::BasicBlock::Create(Context, "ForCond");
	llvm::BasicBlock* ForLoopBB = llvm::BasicBlock::Create(Context, "ForLoop");
	llvm::BasicBlock* ForTailBB = llvm::BasicBlock::Create(Context, "ForTail");
	llvm::BasicBlock* ForEndBB = llvm::BasicBlock::Create(Context, "ForEnd");
  //init

	if (this->a) 
  {
		__Generator.PushSymbolTable();
		this->a->codegen(__Generator);
	}

	TerminateBlockByBr(ForCondBB);
	//cond
	CurrentFunc->getBasicBlockList().push_back(ForCondBB);
	IRBuilder.SetInsertPoint(ForCondBB);
	if (this->b) 
  {
		llvm::Value* Condition = this->b->codegen(__Generator);
		if (!(Condition = Cast2I1(Condition))) 
    {
				throw std::logic_error("The condition value of for-statement is wrong.");
				return NULL;
		}
		IRBuilder.CreateCondBr(Condition, ForLoopBB, ForEndBB);
	}
	else IRBuilder.CreateBr(ForLoopBB);
	
  //lp
	CurrentFunc->getBasicBlockList().push_back(ForLoopBB);
	IRBuilder.SetInsertPoint(ForLoopBB);
	if (this->t) 
  {
		__Generator.EnterLoop(ForTailBB, ForEndBB);	
		__Generator.PushSymbolTable();
		this->t->codegen(__Generator);
		__Generator.PopSymbolTable();
		__Generator.LeaveLoop();
	}
	
  //tail
	TerminateBlockByBr(ForTailBB);
	CurrentFunc->getBasicBlockList().push_back(ForTailBB);
	IRBuilder.SetInsertPoint(ForTailBB);
	if (this->c) this->c->codegen(__Generator);
	IRBuilder.CreateBr(ForCondBB);
	
  //end
	CurrentFunc->getBasicBlockList().push_back(ForEndBB);
	IRBuilder.SetInsertPoint(ForEndBB);
	if (this->a) __Generator.PopSymbolTable();
	return NULL;
}





llvm::Value* AST::Exp_ID::CodeGenPtr(CodeGenerator& __Generator)
{
    llvm::Value* VarPtr = __Generator.FindVariable(ID_Name);
		if (VarPtr) 
      std::cout<<"undefined variable\n";
    return VarPtr;
    
}

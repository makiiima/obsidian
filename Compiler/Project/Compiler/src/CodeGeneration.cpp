#include "CodeGeneration.hpp"

llvm::LLVMContext Context;
llvm::IRBuilder<> IRBuilder(Context);
CodeGenerator::CodeGenerator(void) :
	Module(new llvm::Module("main", Context)),
	DL(new llvm::DataLayout(Module)),
	CurrFunction(NULL),
	SymbolTableStack(),
	ContinueBlockStack(),
	BreakBlockStack(),
	TmpBB(NULL),
	TmpFunc(NULL),
	printf(getPrintf())
{}


void CodeGenerator::DumpIRCode(std::string FileName) 
{
	if (FileName == "") FileName = "-";
	std::error_code EC;
	llvm::raw_fd_ostream Out(FileName, EC);
	Out << "*****************  IRCode  ****************\n";
	this->Module->print(Out, NULL);
	Out << "***************  Verification  ***************\n";
	if (llvm::verifyModule(*this->Module, &Out) == 0) Out << "No errors.\n";
}

//add
bool CodeGenerator::AddFunction(std::string nm, llvm::Function* Function) 
{
	if(this->SymbolTableStack.size() == 0) return false;

	auto& TT = *(this->SymbolTableStack.back());
	auto Pi = TT.find(nm);
	if (Pi != TT.end()) return false;
	TT[nm] = Symbol(Function);
	return true;
}
bool CodeGenerator::AddVariable(std::string NM, llvm::Value* Variable) 
{
	if (this->SymbolTableStack.size() == 0) return false;
	auto& TT = *(this->SymbolTableStack.back());
	auto Pi = TT.find(NM);
	if (Pi != TT.end()) return false;
	TT[NM] = Symbol(Variable, false);
	return true;
}
bool CodeGenerator::AddConstant(std::string NM, llvm::Value* Constant) 
{
	if (this->SymbolTableStack.size() == 0) return false;
	auto& TT = *(this->SymbolTableStack.back());
	auto Pi = TT.find(NM);
	if (Pi != TT.end()) return false;
	TT[NM] = Symbol(Constant, true);
	return true;
}

//push&pop
void CodeGenerator::PushSymbolTable(void) 
{
	//this->SymbolTableStack.push_back(SymbolTable);
	this->SymbolTableStack.push_back(new SymbolTable);
}
void CodeGenerator::PopSymbolTable(void) 
{
	if (this->SymbolTableStack.size() <= 0) return;
	delete this->SymbolTableStack.back();
	this->SymbolTableStack.pop_back();
}

void CodeGenerator::GenObjectCode(std::string FileName) 
{
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();
  auto TargetTriple = llvm::sys::getDefaultTargetTriple();
  Module->setTargetTriple(TargetTriple);
  std::string Error;
  auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
  if (!Target) 
  {
    std::cout << Error;
    return ;
  }
  auto CPU = "generic";
  auto Features = "";
  llvm::TargetOptions opt;
  auto RM = llvm::Optional<llvm::Reloc::Model>();
  auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
  Module->setDataLayout(TheTargetMachine->createDataLayout());
//Module->setDataLayout(TheTargetMachine->createDataLayout());
  auto Filename = "output.o";

  std::error_code EC;
  llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

  if(EC) 
  {
    std::cout << "Could not open file: " << EC.message();
    return ;
  }

  llvm::legacy::PassManager pass;
  auto FileType = llvm::CGFT_ObjectFile;

  pass.run(*Module);
  dest.flush();
  std::cout<< "Wrote " << Filename << "\n";
}

//about lp
void CodeGenerator::EnterLoop(llvm::BasicBlock* CBB, llvm::BasicBlock* BBB) 
{
	this->ContinueBlockStack.push_back(CBB);
	this->BreakBlockStack.push_back(BBB);
}
void CodeGenerator::LeaveLoop(void) 
{
	//empty
	if (this->ContinueBlockStack.size() == 0 || this->BreakBlockStack.size() == 0) return;
	this->ContinueBlockStack.pop_back();
	this->BreakBlockStack.pop_back();
}

//find
llvm::Function* CodeGenerator::FindFunction(std::string Name) 
{
	//empty
	if(this->SymbolTableStack.size() == 0) return NULL;
	//for(auto iter = this->SymbolTableStack.end() - 1; iter >= this->SymbolTableStack.begin(); --TableIter)
	for (auto TableIter = this->SymbolTableStack.end() - 1; TableIter >= this->SymbolTableStack.begin(); --TableIter) 
	{
		auto PairIter = (**TableIter).find(Name);
		if (PairIter != (**TableIter).end()) return PairIter->second.GetFunction();
	}
	return NULL;
}

llvm::Value* CodeGenerator::FindVariable(std::string Name) 
{
	//emtpy
	if(this->SymbolTableStack.size() == 0) return NULL;
	for(auto TableIter = this->SymbolTableStack.end() - 1; TableIter >= this->SymbolTableStack.begin(); --TableIter) 
	{
		auto PairIter = (**TableIter).find(Name);
		if(PairIter != (**TableIter).end())
			return PairIter->second.GetVariable();
	}
	return NULL;
}
llvm::Value* CodeGenerator::FindConstant(std::string Name) 
{
	//emtpy
	if(this->SymbolTableStack.size() == 0) return NULL;
	for(auto TableIter = this->SymbolTableStack.end() - 1; TableIter >= this->SymbolTableStack.begin(); --TableIter) 
	{
		auto PairIter = (**TableIter).find(Name);
		if(PairIter != (**TableIter).end())
			return PairIter->second.GetConstant();
	}
	return NULL;
}

void CodeGenerator::XIPBB(void) 
{
	auto Tmp = IRBuilder.GetInsertBlock();
	IRBuilder.SetInsertPoint(this->TmpBB);
	this->TmpBB = Tmp;
}

void CodeGenerator::EnterFunction(llvm::Function* Func) 
{
	this->CurrFunction = Func;
}
void CodeGenerator::LeaveFunction(void) 
{
	this->CurrFunction = NULL;
}
llvm::Function* CodeGenerator::GetCurrentFunction(void) 
{
	return this->CurrFunction;
}

llvm::BasicBlock* CodeGenerator::GetContinueBlock(void) 
{
	if (this->ContinueBlockStack.size()) return this->ContinueBlockStack.back();
	else return NULL;
}
llvm::BasicBlock* CodeGenerator::GetBreakBlock(void) 
{
	if (this->BreakBlockStack.size()) return this->BreakBlockStack.back();
	else return NULL;
}

void CodeGenerator::GenerateCode(AST::Program& Root, const std::string& OptimizeLevel) 
{

	//Module->setDataLayout(TheTargetMachine->createDataLayout());
	this->PushSymbolTable();
	this->TmpFunc = llvm::Function::Create(llvm::FunctionType::get(IRBuilder.getVoidTy(), false), llvm::GlobalValue::InternalLinkage, "0Tmp", this->Module);
	this->TmpBB = llvm::BasicBlock::Create(Context, "Temp", this->TmpFunc);
	Root.codegen(*this);
	//gensuc
	std::cout << "Gen Successfully" << std::endl;
	std::cout << "Write IR to test.ll" << std::endl;

	//module
	this->TmpBB->eraseFromParent();
	this->TmpFunc->eraseFromParent();
	this->PopSymbolTable();

	if (OptimizeLevel != "") 
	{
		llvm::LoopAnalysisManager LAM;
		llvm::FunctionAnalysisManager FAM;
		llvm::CGSCCAnalysisManager CGAM;
		llvm::ModuleAnalysisManager MAM;
		llvm::PassBuilder PB;
		PB.registerModuleAnalyses(MAM);
		PB.registerCGSCCAnalyses(CGAM);
		PB.registerFunctionAnalyses(FAM);
		PB.registerLoopAnalyses(LAM);
		PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);
		//Create the pass manager.
		const llvm::OptimizationLevel* OptLevel; OptLevel = &llvm::OptimizationLevel::O1;
		llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(*OptLevel);
		std::cout<<"optimize done\n";
	}
}

llvm::Function* CodeGenerator::getPrintf()
{
  std::vector<llvm::Type*> printf_arg_types; //printf内参数的类型
  printf_arg_types.push_back(IRBuilder.getInt8PtrTy()); //8位代表void*

  llvm::FunctionType* printf_type = llvm::FunctionType::get(IRBuilder.getInt32Ty(),printf_arg_types,true);
  llvm::Function* printf_func = llvm::Function::Create(printf_type,llvm::Function::ExternalLinkage,llvm::Twine("printf"),this->Module);

  printf_func->setCallingConv(llvm::CallingConv::C);
  return printf_func;
}

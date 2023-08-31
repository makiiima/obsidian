#include <iostream>
#include <fstream>
#include "AST.hpp"
#include "CodeGeneration.hpp"
extern int yyparse();
extern AST::Program* root;
//extern llvm::Module * TheModule;

int main()
{
    CodeGenerator Gen;
    std::string input_path = "../test/input.c";
    freopen(input_path.c_str(), "r", stdin);
    yyparse();
    root->visualization(0, "../visualization_text.txt");
    try
    {
        Gen.GenerateCode(*root, "O0");
    }
    catch(std::exception& e)
    {
        #if defined(__unix__)
		//Unix platform
		std::cout << "\033[31m" << e.what() << std::endl;
    #endif
    }
    Gen.GenObjectCode("Compiler.o");
    llvm::StringRef outputStr = "../test.ll";
	std::error_code EC;
	llvm::raw_fd_ostream output(outputStr, EC);
    Gen.Module->print(output,NULL);
    std::cout<<"gen down\n";
    //root->codegen(Gen);
    //TheModule->print(llvm::outs(),NULL);
}
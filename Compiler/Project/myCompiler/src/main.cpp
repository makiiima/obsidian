#include <cstdio>
#include <fstream>
#include <iostream>
#include "ast.hpp"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *s);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }

  const char *inputFileName = argv[1];

  // 读取输入文件内容并进行编译处理
  yyin = fopen(inputFileName, "r");
  // 在这里执行编译过程，将输入文件内容转换为 LLVM IR

  yyparse();
  fclose(yyin);

  return 0;
}

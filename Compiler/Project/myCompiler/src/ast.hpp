#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class BaseAST {
public:
  virtual ~BaseAST() = default;
};

class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;
};

class FuncDefAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;
};

class FuncTypeAST : public BaseAST {
public:
  std::string type;
};

class BlockAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;
};

class StmtAST : public BaseAST {
public:
  int number;
};

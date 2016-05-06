#include "VarDecl.hpp"

using namespace std;
using namespace ast;

VarDecl::VarDecl(Type * type, string name) : type(type), name(name) {}

VarDecl::~VarDecl() { 
  if (type)
    delete type; 
}

string VarDecl::to_string() const {
  string res = "";
  res += "VarDecl " + type->to_string() + " " + name;
  return res;
}

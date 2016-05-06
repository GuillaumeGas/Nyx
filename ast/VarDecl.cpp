#include "VarDecl.hpp"

using namespace std;

VarDecl::VarDecl(Type * type, string name) : m_type(type), m_name(name) {}

VarDecl::~VarDecl() { 
  if (m_type)
    delete m_type; 
}

string VarDecl::to_string(int padd) {
  string res = "";
  for(int i = 0; i < padd; i++) { res += " "; }
  res += "VarDecl " + type.to_string() + " " name;
  return res;
}

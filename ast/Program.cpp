#include "Program.hpp"

using namespace std;
using namespace ast;

Program::~Program() {
  for(Ast* a : content) {
    if (a)
      delete a;
  }
}

string Program::to_string() const {
  string res = "";
  res += "BEGIN\n";
  for(Ast* a : content) {
    res += a->to_string();
  }
  res += "\nEND";
  return res;
}

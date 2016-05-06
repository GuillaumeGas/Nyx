#include "Program.hpp"

using namespace std;
using namespace ast;

Program::~Program() {
  for(Declaration* d : declarations) {
    if (d)
      delete d;
  }
}

string Program::to_string(int padd) const {
  string res = "";
  res += "BEGIN\n";
  for(Declaration* d : declarations) {
    res += d->to_string(padd);
  }
  res += "\nEND";
  return res;
}

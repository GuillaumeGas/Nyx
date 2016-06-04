#include "Program.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Program::Program() {
  pos = new Position(0, 0);
}

Program::~Program() {
  for(Ast* a : content) {
    if (a) {
      delete a;
    }
  }
}

void Program::interpret() {
  for (Ast * a : content) {
    a->interpret();
  }
}

string Program::to_string() const {
  string res = "";
  res += "BEGIN\n";
  for(Ast* a : content) {
    res += a->to_string() + "\n";
  }
  res += "\nEND";
  return res;
}

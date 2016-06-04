#include "Ast.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Ast::~Ast() {
  if (pos) {
    delete pos;
  }
}

std::string Ast::to_string() const { return "ROOT"; }

void Ast::interpret() {  }

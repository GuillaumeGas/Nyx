#include "Ast.hpp"

using namespace ast;

Ast::~Ast() {
  if (pos) {
    delete pos;
  }
}

std::string Ast::to_string() const { return "ROOT"; }

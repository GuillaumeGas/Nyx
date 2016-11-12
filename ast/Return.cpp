#include "Return.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Return::Return (Expression * expr, Position * pos) {
  this->expr = expr;
  this->pos = pos;
}

Return::~Return () {
  if (expr)
    delete expr;
}

void Return::interpret () {}

void Return::print (ostream & out, int offset) const {
  shift (out, offset);
  out << "Return";
  if (expr) {
    out << " ";
    expr->print (out);
  }
}

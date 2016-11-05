#include "PrintI.hpp"

using namespace std;
using namespace bob;
using namespace ast;

PrintI::PrintI(Expression * expr, Position * pos) : expr(expr) {
  this->pos = pos;
}

PrintI::~PrintI() {
  if (expr)
    delete expr;
}

void PrintI::interpret() const {
    Expression * e = expr->interpret_expr();
    cout << e->get_value()->Int;
}

string PrintI::to_string() const {
  return "print_i " + expr->to_string();
}

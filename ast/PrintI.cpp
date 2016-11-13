#include "PrintI.hpp"

using namespace std;
using namespace nyx;
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

void PrintI::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "print_i ";
    expr->print (out);
}

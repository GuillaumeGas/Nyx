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
    Expression * e = expr->interpretExpression ();
    if (e->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, e->getType (), pos);
    }
    cout << e->getValue()->getInt ();
}

void PrintI::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "print_i ";
    expr->print (out);
}

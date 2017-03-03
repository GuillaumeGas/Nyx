#include "Cast.hpp"
#include "Expression.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Cast::Cast (Type * type, ExpressionPtr expr, Position * pos) {
    this->type = type;
    this->expr = expr;
    this->pos = pos;
}

Cast::~Cast () {
    if (type)
	delete type;
}

void Cast::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "cast:" << type->toString () << "(";
    expr->print (out);
    out << ")";
}

ExpressionPtr Cast::interpretExpression () {
    return NullExpression ();
}

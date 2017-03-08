#include "Cast.hpp"
#include "Expression.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Cast::Cast (Type * type, ExpressionPtr expr, Position * pos) : Expression (pos) {
    _type = type;
    _expr = expr;
}

Cast::~Cast () {
    if (_type)
	delete _type;
}

void Cast::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "cast:" << _type->toString () << "(";
    _expr->print (out);
    out << ")";
}

ExpressionPtr Cast::interpretExpression () {
    return NullExpression ();
}

Type * Cast::getType () const {
    return _type;
}

void Cast::setType (Type * type) {
    if (_type)
	delete _type;
    _type = type;
}

ExpressionPtr Cast::getExpr () const {
    return _expr;
}

void Cast::setExpr (ExpressionPtr expr) {
    _expr = expr;
}

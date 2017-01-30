#include "Cast.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Cast::Cast (Type * type, Expression * expr, Position * pos) {
    this->type = type;
    this->expr = expr;
    this->pos = pos;
}

Cast::~Cast () {
    if (type)
	delete type;
    if (expr)
	delete expr;
}

void Cast::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "cast:" << type->toString () << "(";
    expr->print (out);
    out << ")";
}

AbstractObject * Cast::interpretExpression () {
    return NULL;
}

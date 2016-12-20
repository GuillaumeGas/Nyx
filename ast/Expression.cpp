#include "Expression.hpp"

using namespace nyx;
using namespace ast;

Expression::Expression () {}

Expression::~Expression() {
    if (type)
	delete type;
    if (value)
	delete value;
}

Expression * Expression::interpretExpression () { return NULL; }

void Expression::interpret() {
    interpretExpression ();
}

Type * Expression::getType() const {
    return type;
}

Value * Expression::getValue () const {
    return value;
}



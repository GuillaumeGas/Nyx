#include "Expression.hpp"

using namespace nyx;
using namespace ast;

Expression::Expression () {
    this->value = new Value;
}

Expression::~Expression() {
    if (type)
	delete type;
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



#include "Expression.hpp"

using namespace nyx;
using namespace ast;

Expression::Expression () {}

Expression::~Expression() {
    if (value)
	delete value;
}

void Expression::interpret() {
    interpretExpression ();
}

Value * Expression::getValue () const {
    return value;
}



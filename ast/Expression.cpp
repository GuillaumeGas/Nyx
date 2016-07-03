#include "Expression.hpp"

using namespace bob;
using namespace ast;

Expression::~Expression() {
  if (type)
    delete type;
}

Expression * Expression::interpret_expr() { return NULL; }

Expression * Expression::sum(Expression * expr) { return NULL; }

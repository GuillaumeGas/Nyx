#include "Expression.hpp"

using namespace bob;
using namespace ast;

Expression::~Expression() {
  if (type)
    delete type;
}

Expression * Expression::interpret_expr() { return NULL; }

Expression * Expression::sum(Expression * expr) { return NULL; }

void Expression::interpret() {
    interpret_expr();
}

Type * Expression::get_type() const {
    return type;
}

int Expression::get_int() { return 0; }

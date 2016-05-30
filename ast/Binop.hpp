#pragma once

#include <iostream>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace ast {
  struct Binop : public Expression {
    Binop(Expression * e1, Expression * e2, const BinOperator op, Position * pos);
    ~Binop();

    std::string to_string() const;

    Expression * e1;
    Expression * e2;
    BinOperator op;
  };
};

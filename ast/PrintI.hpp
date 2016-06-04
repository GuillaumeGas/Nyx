#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace ast {
  class PrintI : public Ast {
  public:
    PrintI(Expression * expr, Position * pos);
    ~PrintI();

    std::string to_string() const;

    Expression * expr;
  };
};

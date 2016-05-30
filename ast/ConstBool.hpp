#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace ast {
  class ConstBool : public Expression {
  public:
    ConstBool(bool value, Position * pos);
    ~ConstBool();

    bool get_value() const;
    std::string to_string() const;

    bool value;
  };
};

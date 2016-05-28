#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace ast {
  class ConstString : public Expression {
  public:
    ConstString(std::string value, Position * pos);
    ~ConstString();

    std::string get_value() const;
    std::string to_string() const;

    std::string value;
  };
};

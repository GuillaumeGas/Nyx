#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace ast {
  class ConstChar : public Expression {
  public:
    ConstChar(const char value, Position * pos);
    ~ConstChar();
    
    char get_value() const;
    std::string to_string() const;

    char value;
  };
};

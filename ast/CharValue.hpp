#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Value.hpp"
#include "Position.hpp"

namespace ast {
  class CharValue : public Value {
  public:
    CharValue(const char value, Position * pos);
    
    char get_value() const;
    std::string to_string() const;

    char value;
  };
};

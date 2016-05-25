#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Value.hpp"
#include "Position.hpp"

namespace ast {
  class IntValue : public Value {
  public:
    IntValue(int value, Position * pos);

    std::string to_string() const;

    int value;
  };
};

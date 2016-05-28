#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Value.hpp"
#include "Position.hpp"

namespace ast {
  class ConstInt : public Value {
  public:
    ConstInt(int value, Position * pos);

    std::string to_string() const;

    int value;
  };
};

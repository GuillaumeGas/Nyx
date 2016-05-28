#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Value.hpp"
#include "Position.hpp"

namespace ast {
  class ConstString : public Value {
  public:
    ConstString(std::string value, Position * pos);

    std::string get_value() const;
    std::string to_string() const;

    std::string value;
  };
};

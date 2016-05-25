#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Value.hpp"
#include "Position.hpp"

namespace ast {
  class StringValue : public Value {
  public:
    StringValue(std::string value, Position * pos);
    
    std::string to_string() const;

    std::string value;
  };
};

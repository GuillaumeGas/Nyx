#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Position.hpp"
#include "Value.hpp"

namespace ast {
  class VarAssign : public Ast {
  public:
    VarAssign(std::string var_name, Value * value, Position * pos);
    ~VarAssign();

    std::string to_string() const;

    std::string name;
    Value * value;
  };
};

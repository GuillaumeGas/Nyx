#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace ast {
  class VarId : public Expression {
  public:
    VarId(std::string name, Position * pos);
    ~VarId();

    std::string to_string() const;
    
    std::string name;
  };
};

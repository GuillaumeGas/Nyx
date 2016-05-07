#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Type.hpp"
#include "Position.hpp"

namespace ast {
  class VarDecl : public Ast {
  public:
    VarDecl(Type * type, std::string name, Position * pos);
    ~VarDecl();

    std::string to_string() const;

    Type * type;
    std::string name;
  };
};

#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Type.hpp"

namespace ast {
  class VarDecl : public Ast {
  public:
    VarDecl(Type * type, std::string name);
    ~VarDecl();

    std::string to_string() const;

    Type * type;
    std::string name;
  };
};

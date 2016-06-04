#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Position.hpp"
#include "Expression.hpp"

namespace bob {
  namespace ast {
    class VarAssign : public Ast {
    public:
      VarAssign(std::string var_name, Expression * value, Position * pos);
      ~VarAssign();

      std::string to_string() const;

      std::string name;
      Expression * value;
    };
  };
};

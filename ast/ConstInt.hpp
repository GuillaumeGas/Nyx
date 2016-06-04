#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace bob {
  namespace ast {
    class ConstInt : public Expression {
    public:
      ConstInt(int value, Position * pos);
      ~ConstInt();

      std::string to_string() const;

      int value;
    };
  };
};

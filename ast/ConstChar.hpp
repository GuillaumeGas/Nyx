#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace bob {
  namespace ast {
    class ConstChar : public Expression {
    public:
      ConstChar(const char value, Position * pos);
      ~ConstChar();
      std::string to_string() const;
    };
  };
};

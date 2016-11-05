#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace bob {
  namespace ast {
    class ConstBool : public Expression {
    public:
      ConstBool(bool value, Position * pos);
      ~ConstBool();

      std::string to_string() const;
    };
  };
};

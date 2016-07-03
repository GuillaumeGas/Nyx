#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"

namespace bob {
  namespace ast {
    class ConstInt : public Expression {
    public:
      ConstInt(int value, Position * pos);
      ~ConstInt();

      std::string to_string() const;
      Expression * interpret_expr();

      Expression * sum(Expression * expr);

      int value;
    };
  };
};

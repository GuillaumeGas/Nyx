#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Type.hpp"

namespace bob {
  namespace ast {
    class Expression : public Ast {
    public:
      virtual ~Expression();
      virtual std::string to_string() const = 0;
      virtual Expression * interpret_expr();
      virtual Expression * sum(Expression * expr);

      Type * type;
    };
  };
};

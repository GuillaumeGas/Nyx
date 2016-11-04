#pragma once

#include <iostream>
#include "../Token.hpp"
#include "../../ast/Ast.hpp"
#include "../../ast/Expression.hpp"
#include "../../ast/Operator.hpp"
#include "../../ast/Binop.hpp"
#include "../../ast/VarId.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Ident {
    public:
      static Ast * analyze(bob::Syntax * syntax, Token * token_ident);
    };
  };
};

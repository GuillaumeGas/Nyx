#pragma once

#include <iostream>
#include "Position.hpp"
#include "Expression.hpp"
#include "../exceptions/SyntaxException.hpp"
#include "../Token.hpp"
#include "../../ast/VarAssign.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Assign {
    public:
      static void analyze(bob::Syntax * syntax, Token * token_name);
    };
  };
};

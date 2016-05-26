#pragma once

#include <iostream>
#include "Position.hpp"
#include "../exceptions/SyntaxException.hpp"
#include "../Token.hpp"
#include "../../ast/VarAssign.hpp"
#include "../../ast/IntValue.hpp"
#include "../../ast/StringValue.hpp"
#include "../../ast/CharValue.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Assign {
    public:
      static void analyze(bob::Syntax * syntax, unsigned int index);
    };
  };
};

#pragma once

#include <iostream>
#include "Position.hpp"
#include "../exceptions/SyntaxException.hpp"
#include "../Token.hpp"
#include "../../ast/VarAssign.hpp"
#include "../../ast/ConstInt.hpp"
#include "../../ast/ConstString.hpp"
#include "../../ast/ConstChar.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Assign {
    public:
      static void analyze(bob::Syntax * syntax, unsigned int index);
    };
  };
};

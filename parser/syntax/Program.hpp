#pragma once

#include <iostream>
#include "InstructionBloc.hpp"
#include "../Syntax.hpp"
#include "../Token.hpp"
#include "../../ast/InstructionBloc.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Program {
    public:
      static void visit(Syntax * syntax);
    };
  };
};

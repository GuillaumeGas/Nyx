#pragma once

#include <iostream>
#include "../Token.hpp"
#include "../../ast/VarAssign.hpp"
#include "../../ast/IntValue.hpp"
#include "../../ast/StringValue.hpp"

class Syntax;

namespace syntax {
  class Assign {
  public:
    static void analyze(Syntax * syntax, unsigned int index);
  };
};

#pragma once

#include <iostream>
#include "../Token.hpp"
#include "../../ast/VarDecl.hpp"
#include "../../ast/Type.hpp"
#include "../../ast/Position.hpp"
#include "Assign.hpp"

class Syntax;

namespace syntax {
  class Type {
  public:
    static void analyze(Syntax * syntax, unsigned int index);
  };
};

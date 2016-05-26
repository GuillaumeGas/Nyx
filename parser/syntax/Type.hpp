#pragma once

#include <iostream>
#include "../Token.hpp"
#include "../../ast/VarDecl.hpp"
#include "../../ast/Type.hpp"
#include "../../ast/Position.hpp"
#include "Assign.hpp"
#include "VarDecl.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Type {
    public:
      static void analyze(bob::Syntax * syntax, unsigned int index);
    };
  };
};

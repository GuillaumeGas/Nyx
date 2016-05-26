#pragma once

#include "../../ast/VarDecl.hpp"
#include "../../ast/Type.hpp"
#include "../Syntax.hpp"
#include "../Token.hpp"
#include "Program.hpp"

namespace bob {
  namespace syntax {
    class VarDecl {
    public:
      static void analyze(Syntax * syntax, unsigned int index, Token * token_type, Token * token_name);
    };
  };
};

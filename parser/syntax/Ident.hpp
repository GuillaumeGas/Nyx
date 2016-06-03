#pragma once

#include <iostream>
#include "../Token.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Ident {
    public:
      static void analyze(bob::Syntax * syntax, Token * token_ident);
    };
  };
};

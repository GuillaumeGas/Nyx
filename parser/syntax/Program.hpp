#pragma once

#include <iostream>
#include "../Token.hpp"
#include "Type.hpp"
#include "Ident.hpp"
#include "PrintI.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Program {
    public:
      static void analyze(Syntax * syntax);
    };
  };
};

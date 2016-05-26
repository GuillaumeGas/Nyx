#pragma once

#include <iostream>
#include "../Token.hpp"
#include "Type.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Program {
    public:
      static void analyze(bob::Syntax * syntax, unsigned int index);
    };
  };
};

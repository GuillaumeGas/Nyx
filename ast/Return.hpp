#pragma once

#include <iostream>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Expression.hpp"

namespace nyx {
  namespace ast {
    class Return : public Ast {
    public:
      Return (Expression * expr, Position * pos);
      ~Return ();

      void print (std::ostream & out, int offset = 0) const;
      void interpret ();

    private:
      Expression * expr;
    };
  };
};

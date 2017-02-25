#pragma once

#include <iostream>
#include "Ast.hpp"
#include "../global/Position.hpp"

namespace nyx {
  namespace ast {
    class Break : public Ast {
    public:
      Break (std::string * ident, Position * pos);
      ~Break ();

      void interpret ();
      void print (std::ostream & out, int offset = 0) const;

    private:
      std::string * ident;
    };
  };
};

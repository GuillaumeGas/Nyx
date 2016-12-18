#pragma once

#include <iostream>
#include <map>
#include <sstream>

#include "Symbol.hpp"
#include "exceptions/SymbolException.hpp"
#include "../global/Global.hpp"
#include "../ast/Position.hpp"

namespace nyx {
  namespace symbol {
    class Scope {
    public:
      Scope(Scope * parent = NULL);
      ~Scope();

      Scope * newScope();
      Scope * getParent();
      void addSymbol(Symbol * s, ast::Position * pos);
      Symbol * getSymbol(std::string name, ast::Position * pos);

      std::string toString() const;

    private:
      std::map<std::string, Symbol*> list;
      Scope * parent_scope;
      Scope * next_scope;
    };
  };
};

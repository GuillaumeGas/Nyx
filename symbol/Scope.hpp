#pragma once

#include <iostream>
#include <map>

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

      Scope * new_scope();
      Scope * get_parent();
      void add_symbol(Symbol * s, ast::Position * pos);
      Symbol * get_symbol(std::string name, ast::Position * pos);

      std::string to_string() const;

    private:
      std::map<std::string, Symbol*> list;
      Scope * parent_scope;
      Scope * next_scope;
    };
  };
};

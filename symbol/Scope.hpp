#pragma once

#include <iostream>
#include <map>

#include "Symbol.hpp"

namespace bob {
  namespace symbol {
    class Scope {
    public:
      Scope(Scope * parent = NULL);
      ~Scope();

      Scope * new_scope();
      Scope * get_parent();
      void add_symbol(Symbol * s);
      Symbol * get_symbol(std::string name);

      std::string to_string() const;

    private:
      std::map<std::string, Symbol*> list;
      Scope * parent_scope;
      Scope * next_scope;
    };
  };
};

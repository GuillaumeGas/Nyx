#pragma once

#include <iostream>
#include "Symbol.hpp"
#include "Scope.hpp"

namespace bob {
  namespace symbol {
    class Table {
    public:
      static Table * get_instance();
      
      void enter_block();
      void exit_block();
      void add_symbol(Symbol * s);
      Symbol * get_symbol(std::string name);

      std::string to_string() const;

    private:
      Table();
      ~Table();

      static Table * instance;

      Scope main_scope;
      Scope * current_scope;
    };
  };
};

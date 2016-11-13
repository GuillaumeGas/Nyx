#pragma once

#include <iostream>
#include "Symbol.hpp"
#include "Scope.hpp"
#include "../ast/Position.hpp"

namespace nyx {
  namespace symbol {
    class Table {
    public:
      static Table * get_instance();
      
      void enter_block();
      void exit_block();
      void add_symbol(Symbol * s, ast::Position * pos);
      Symbol * get_symbol(std::string name, ast::Position * pos);

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

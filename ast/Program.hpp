#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"

namespace ast {
  class Program : public Ast {
  public:
    ~Program();

    std::string to_string() const;

    std::vector<Ast*> content;
  };
};

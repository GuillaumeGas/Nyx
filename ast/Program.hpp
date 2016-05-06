#pragma once

#include <iostream>
#include <vector>

#include "Declaration.hpp"

namespace ast {
  class Program : public Ast {
  public:
    ~Program();

    std::string to_string(int padd) const;

    std::vector<Declaration*> declarations;
  };
};

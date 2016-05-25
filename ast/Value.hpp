#pragma once

#include <iostream>
#include "Ast.hpp"

namespace ast {
  class Value : public Ast {
  public:
    Value();
    ~Value();
    virtual std::string to_string() const;
  };
};

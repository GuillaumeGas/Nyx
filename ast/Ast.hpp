#pragma once

#include <iostream>

#include "Position.hpp"

namespace ast {
  class Ast {
  public:
    virtual ~Ast();
    virtual std::string to_string() const;
    Position * pos;
  };
}

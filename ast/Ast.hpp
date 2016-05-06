#pragma once

#include <iostream>

namespace ast {
  class Ast {
  public:
    virtual ~Ast();
    virtual std::string to_string() const;
    //    Position position;
  };
}

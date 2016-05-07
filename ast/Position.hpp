#pragma once

#include <iostream>

namespace ast {
  class Position {
  public:
    Position(unsigned int line, unsigned int column);
    ~Position();
    std::string to_string() const;
    unsigned int line;
    unsigned int column;
  };
};

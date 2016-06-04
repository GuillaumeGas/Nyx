#pragma once

#include <iostream>

namespace bob {
  namespace ast {
    class Position {
    public:
      Position(unsigned int line, unsigned int column);
      Position(const Position& p);
      ~Position();
      std::string to_string() const;
      unsigned int line;
      unsigned int column;
    };
  };
};

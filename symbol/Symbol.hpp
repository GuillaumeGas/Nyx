#pragma once

#include <iostream>

namespace bob {
  namespace symbol {
    class Symbol {
    public:
      Symbol(std::string name);

      std::string to_string() const;

      std::string name;
    };
  };
};

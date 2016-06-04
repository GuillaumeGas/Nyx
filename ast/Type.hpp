#pragma once

#include <iostream>

namespace bob {
  namespace ast {
    class Type {
    public:
      Type(std::string name, bool is_basic);
      ~Type();

      std::string to_string() const;
    
      std::string name;
      bool is_basic;
    };
  };
};

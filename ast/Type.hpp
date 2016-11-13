#pragma once

#include <iostream>

namespace nyx {
  namespace ast {
    enum TYPE {
      INT,
      CHAR,
      ERR
    };

    class Type {
    public:
      Type(std::string name, bool is_basic);
      ~Type();

      std::string to_string() const;
      TYPE get_type() const;

      TYPE type;
      std::string name;
      bool is_basic;
    };

  };
};

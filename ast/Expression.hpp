#pragma once

#include <iostream>
#include "Ast.hpp"

namespace bob {
  namespace ast {
    class Expression : public Ast {
    public:
      virtual ~Expression();
      virtual std::string to_string() const = 0;
    };
  };
};

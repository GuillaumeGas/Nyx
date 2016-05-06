#pragma once

#include <iostream>
#include "Type.hpp"

namespace ast {
  class VarDecl {
  public:
    VarDecl(Type * type, std::string name);
    ~VarDecl();

    std::string to_string(int padd) const;

    Type * m_type;
    std::string m_name;
  };
};

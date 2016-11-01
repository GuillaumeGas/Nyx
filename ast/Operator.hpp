#pragma once

#include <iostream>

namespace bob {
  namespace ast {

    enum OpPriority {
      UUULOW_OP,
      UULOW_OP,
      ULOW_OP,
      LOW_OP,
      HIGH_OP
    };

    enum Op {
      PLUS,
      MINUS,
      MUL,
      DIV,
      MOD,
      ASSIGN
    };

    class Operator {
    public:
      Operator(std::string s);
      OpPriority priority;
      Op value;

      std::string to_string() const;

    private:
      Op get_value(std::string s);
      OpPriority get_priority(Op o);
    };

  };
};

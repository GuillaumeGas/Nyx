#pragma once

#include <iostream>

namespace nyx {
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
      ASSIGN,
      LT,
      LE,
      GT,
      GE,
      EQ,
      NE,
      UNKNOWN
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

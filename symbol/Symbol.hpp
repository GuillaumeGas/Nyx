#pragma once

#include <iostream>
#include "../ast/Type.hpp"

namespace nyx {
  namespace symbol {
    class SymbolValue {
    public:
      virtual std::string toString() const = 0;
      ast::Type * type;
    };

    class SymbolIntValue : public SymbolValue {
    public:
      SymbolIntValue(ast::Type * type, int val);

      std::string toString() const;

      int value;
    };

    class SymbolCharValue : public SymbolValue {
    public:
      SymbolCharValue(ast::Type * type, char val);

      std::string toString() const;

      char value;
    };

    class SymbolStringValue : public SymbolValue {
    public:
      SymbolStringValue(ast::Type * type, std::string val);

      std::string toString() const;

      std::string value;
    };

    class Symbol {
    public:
      Symbol(std::string name, ast::Type * type);
      Symbol(std::string name, ast::Type * type, int value);
      Symbol(std::string name, ast::Type * type, char value);
      Symbol(std::string name, ast::Type * type, std::string value);
      ~Symbol();

      void setValue(int value);
      void setValue(char value);
      void setValue(std::string value);

      ast::Type * getType() const;
      std::string toString() const;

      std::string name;
      SymbolValue * symbol_value;
    };
  };
};

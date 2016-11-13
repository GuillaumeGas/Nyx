#pragma once

#include <iostream>
#include "../ast/Type.hpp"

namespace nyx {
  namespace symbol {
    class SymbolValue {
    public:
      virtual std::string to_string() const = 0;
      ast::Type * type;
    };

    class SymbolIntValue : public SymbolValue {
    public:
      SymbolIntValue(ast::Type * type, int val);

      std::string to_string() const;

      int value;
    };

    class SymbolCharValue : public SymbolValue {
    public:
      SymbolCharValue(ast::Type * type, char val);

      std::string to_string() const;

      char value;
    };

    class SymbolStringValue : public SymbolValue {
    public:
      SymbolStringValue(ast::Type * type, std::string val);

      std::string to_string() const;

      std::string value;
    };

    class Symbol {
    public:
      Symbol(std::string name, ast::Type * type);
      Symbol(std::string name, ast::Type * type, int value);
      Symbol(std::string name, ast::Type * type, char value);
      Symbol(std::string name, ast::Type * type, std::string value);
      ~Symbol();

      void set_value(int value);
      void set_value(char value);
      void set_value(std::string value);

      ast::Type * get_type() const;
      std::string to_string() const;

      std::string name;
      SymbolValue * symbol_value;
    };
  };
};

#include "Symbol.hpp"

using namespace std;
using namespace bob;
using namespace symbol;

Symbol::Symbol(string name, ast::Type * type) : name(name) {
  if (type->is_basic) {
    ast::TYPE t = type->get_type();
    if (t == ast::TYPE::INT) {
      symbol_value = new SymbolIntValue(type, 0);
    } else if (t == ast::TYPE::CHAR) {
      char c = -1;
      symbol_value = new SymbolCharValue(type, c);
    } else {
      cout << "[Error] Unknown type.";
      exit(-1);
    }
  } else {
    cout << "[Error] Unknown type.";
    exit(-1);
  }
}
Symbol::Symbol(string name, ast::Type * type, int value) : name(name) {
  symbol_value = new SymbolIntValue(type, value);
}
Symbol::Symbol(string name, ast::Type * type, char value) : name(name) {
  symbol_value = new SymbolCharValue(type, value);
}
Symbol::Symbol(string name, ast::Type * type, string value) : name(name) {
  symbol_value = new SymbolStringValue(type, value);
}

Symbol::~Symbol() {
  if (symbol_value)
    delete symbol_value;
}

void Symbol::set_value(int value) {
  SymbolIntValue * s = (SymbolIntValue * ) symbol_value;
  s->value = value;
}
void Symbol::set_value(char value) {
  SymbolCharValue * s = (SymbolCharValue * ) symbol_value;
  s->value = value;
}
void Symbol::set_value(string value) {
  SymbolStringValue * s = (SymbolStringValue * ) symbol_value;
  s->value = value;
}

ast::Type * Symbol::get_type() const {
  return symbol_value->type;
}

string Symbol::to_string() const {
  return "[" + name + ", " + symbol_value->to_string() + "]";
}

SymbolIntValue::SymbolIntValue(ast::Type * type, int val) : value(val) {
  this->type = type;
}

string SymbolIntValue::to_string() const {
  return "(" + type->to_string() + ") " +  std::to_string(value);
}

SymbolCharValue::SymbolCharValue(ast::Type * type, char val) : value(val) {
  this->type = type;
}

string SymbolCharValue::to_string() const {
  return "(" + type->to_string() + ") " +  std::to_string(value);
}

SymbolStringValue::SymbolStringValue(ast::Type * type, string val) : value(val) {
  this->type = type;
}

string SymbolStringValue::to_string() const {
  return "(" + type->to_string() + ") " +  value;
}




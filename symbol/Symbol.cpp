#include "Symbol.hpp"

using namespace std;
using namespace bob;
using namespace symbol;

Symbol::Symbol(string name, ast::Type * type) : name(name) {
  if (type->is_basic) {
    ast::TYPE t = type->get_type();
    if (t == ast::TYPE::INT) {
      this->value = new SymbolIntValue(type, 0);
    } else if (t == ast::TYPE::CHAR) {
      char c = -1;
      this->value = new SymbolCharValue(type, c);
    } else if (t == ast::TYPE::STRING) {
      string s;
      this->value = new SymbolStringValue(type, s);
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
  this->value = new SymbolIntValue(type, value);
}
Symbol::Symbol(string name, ast::Type * type, char value) : name(name) {
  this->value = new SymbolCharValue(type, value);
}
Symbol::Symbol(string name, ast::Type * type, string value) : name(name) {
  this->value = new SymbolStringValue(type, value);
}

Symbol::~Symbol() {
  if (value)
    delete value;
}

string Symbol::to_string() const {
  return "[" + name + ", " + value->to_string() + "]";
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




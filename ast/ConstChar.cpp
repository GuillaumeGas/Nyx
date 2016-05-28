#include "ConstChar.hpp"

using namespace std;
using namespace ast;

ConstChar::ConstChar(const char value, Position * pos) : value(value) {
  this->pos = pos;
}

char ConstChar::get_value() const {
  return value;
}

string ConstChar::to_string() const {
  string s = "'";
  s.push_back(value);
  s += "'";
  return s;
}

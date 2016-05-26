#include "CharValue.hpp"

using namespace std;
using namespace ast;

CharValue::CharValue(const char value, Position * pos) : value(value) {
  this->pos = pos;
}

char CharValue::get_value() const {
  return value;
}

string CharValue::to_string() const {
  string s = "'";
  s.push_back(value);
  s += "'";
  return s;
}

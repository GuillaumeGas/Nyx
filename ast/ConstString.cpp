#include "ConstString.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstString::ConstString(string value, Position * pos) : value(value) {
  this->pos = pos;
}

ConstString::~ConstString() {}

string ConstString::get_value() const {
  return value;
}

string ConstString::to_string() const {
  return "\"" + value + "\"";
}

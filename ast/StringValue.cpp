#include "StringValue.hpp"

using namespace std;
using namespace ast;

StringValue::StringValue(string value, Position * pos) : value(value) {
  this->pos = pos;
}

string StringValue::get_value() const {
  return value;
}

string StringValue::to_string() const {
  return "\"" + value + "\"";
}

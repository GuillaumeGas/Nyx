#include "StringValue.hpp"

using namespace std;
using namespace ast;

StringValue::StringValue(string value, Position * pos) : value(value) {
  this->pos = pos;
}

string StringValue::to_string() const {
  return value;
}

#include "IntValue.hpp"

using namespace std;
using namespace ast;

IntValue::IntValue(int value, Position * pos) : value(value) {
  this->pos = pos;
}

string IntValue::to_string() const {
  string res = "";
  res += std::to_string(value);
  return res;
}

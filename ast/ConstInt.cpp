#include "ConstInt.hpp"

using namespace std;
using namespace ast;

ConstInt::ConstInt(int value, Position * pos) : value(value) {
  this->pos = pos;
}

string ConstInt::to_string() const {
  string res = "";
  res += std::to_string(value);
  return res;
}

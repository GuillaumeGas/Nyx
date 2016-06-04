#include "ConstInt.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstInt::ConstInt(int value, Position * pos) : value(value) {
  this->pos = pos;
}

ConstInt::~ConstInt() {}

string ConstInt::to_string() const {
  return std::to_string(value);
}


#include "ConstBool.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstBool::ConstBool(bool value, Position * pos) : value(value) {
  this->pos = pos;
}

ConstBool::~ConstBool() {}

bool ConstBool::get_value() const {
  return value;
}

string ConstBool::to_string() const {
  return value ? "true" : "false";
}

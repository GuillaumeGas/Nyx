#include "VarAssign.hpp"

using namespace std;
using namespace ast;

VarAssign::VarAssign(string var_name, Value * value, Position * pos) : name(var_name), value(value) {
  this->pos = pos;
}

VarAssign::~VarAssign() {
  if (value)
    delete value;
}

string VarAssign::to_string() const {
  string res = "";
  res += "VarAssign " + name + " " + value->to_string() + ", " + pos->to_string();
  return res;
}

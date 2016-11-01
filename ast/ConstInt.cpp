#include "ConstInt.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstInt::ConstInt(int value, Position * pos) : value(value) {
  this->pos = pos;
  this->type = new Type("int", true);
}

ConstInt::~ConstInt() {}

string ConstInt::to_string() const {
  return std::to_string(value);
}

Expression * ConstInt::interpret_expr() {
  return this;
}

Expression * ConstInt::sum(Expression * expr) {
  ConstInt * i = (ConstInt *) expr;
  ConstInt * res = new ConstInt(value+i->value, pos);
  cout << "constint : " << res->to_string() << endl;
  return res;
}

int ConstInt::get_int() {
    return value;
}

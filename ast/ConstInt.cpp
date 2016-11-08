#include "ConstInt.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstInt::ConstInt(int v, Position * pos) {
    this->value->Int = v;
    this->pos = pos;
    this->type = new Type("int", true);
}

ConstInt::~ConstInt() {}

void ConstInt::print (ostream & out, int offset) const {
    out << value->Int;
}

Expression * ConstInt::interpret_expr() {
    return this;
}

Expression * ConstInt::sum(Expression * expr) {
    ConstInt * i = (ConstInt *) expr;
    ConstInt * res = new ConstInt(value->Int + i->value->Int, pos);
    return res;
}

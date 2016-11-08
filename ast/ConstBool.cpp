#include "ConstBool.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstBool::ConstBool(bool value, Position * pos) {
    this->value->Bool = value;
    this->pos = pos;
}

ConstBool::~ConstBool() {}

void ConstBool::print (ostream & out, int offset) const {
    out << (value ? "true" : "false");
}

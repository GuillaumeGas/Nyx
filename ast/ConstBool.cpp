#include "ConstBool.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstBool::ConstBool(bool value, Position * pos) {
    this->value->Bool = value;
    this->pos = pos;
}

ConstBool::~ConstBool() {}

string ConstBool::to_string() const {
    return value ? "true" : "false";
}

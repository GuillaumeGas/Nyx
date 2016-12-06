#include "ConstFloat.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

ConstFloat::ConstFloat (float value, Position * pos) {
    this->value->Float = value;
    this->pos = pos;
    this->type = new Type ("float", true);
}

ConstFloat::~ConstFloat () {}

void ConstFloat::print (ostream & out, int offset) const {
    out << std::to_string (this->value->Float);
}

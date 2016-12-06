#include "ConstChar.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

ConstChar::ConstChar(char value, Position * pos) {
    this->value->Char = value;
    this->pos = pos;
}

ConstChar::~ConstChar() {}

void ConstChar::print (ostream & out, int offset) const {
    out << "'" << value->Char << "'";
}

#include "ConstChar.hpp"

using namespace std;
using namespace bob;
using namespace ast;

ConstChar::ConstChar(const char value, Position * pos) {
    this->value->Char = value;
    this->pos = pos;
}

ConstChar::~ConstChar() {}

string ConstChar::to_string() const {
    string s = "'";
    s.push_back(value->Char);
    s += "'";
    return s;
}

#include "ConstString.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

ConstString::ConstString (const string & value, Position * pos) {
    this->value->Str = new string (value);
    this->pos = pos;
    this->type = new Type ("string", true);
}

ConstString::~ConstString () {
    if (this->value->Str)
	delete this->value->Str;
}

void ConstString::print (ostream & out, int offset) const {
    out << *(value->Str);
}


#include "Const.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

ConstBool::ConstBool(bool value, Position * pos) {
    this->value->Bool = value;
    this->pos = pos;
}

ConstBool::~ConstBool() {}

void ConstBool::print (ostream & out, int offset) const {
    out << (value ? "true" : "false");
}

ConstChar::ConstChar(char value, Position * pos) {
    this->value->Char = value;
    this->pos = pos;
}

ConstChar::~ConstChar() {}

void ConstChar::print (ostream & out, int offset) const {
    out << "'" << value->Char << "'";
}

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

ConstFloat::ConstFloat (float value, Position * pos) {
    this->value->Float = value;
    this->pos = pos;
    this->type = new Type ("float", true);
}

ConstFloat::~ConstFloat () {}

void ConstFloat::print (ostream & out, int offset) const {
    out << std::to_string (this->value->Float);
}

ConstString::ConstString (string * value, Position * pos) {
    this->value->Str = value;
    this->pos = pos;
    this->type = new Type ("string", true);
}

ConstString::~ConstString () {
    if (this->value->Str)
	delete this->value->Str;
}

void ConstString::print (ostream & out, int offset) const {
    out << "\"" << *(value->Str) << "\"";
}

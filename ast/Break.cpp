#include "Break.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Break::Break (string * ident, Position * pos) : Instruction (pos) {
    _ident = ident;
}

Break::~Break () {
    if (_ident)
	delete _ident;
}

void Break::interpret () {}

void Break::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "Break";
    if (_ident)
	out << " " << *_ident;
}

#include "Ast.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Ast::Ast (Position * pos) : _pos (pos) {}

Ast::~Ast() {
    if (_pos)
	delete _pos;
}

void Ast::shift (ostream & out, int offset) const {
    for (int i = 0; i < offset; i++)
	out << " ";
}

Position * Ast::getPos () const {
    return _pos;
}

void Ast::setPos (Position * pos) {
    if (_pos)
	delete _pos;
    _pos = pos;
}

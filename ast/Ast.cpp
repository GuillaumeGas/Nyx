#include "Ast.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Ast::~Ast() {
    if (pos)
	delete pos;
}

void Ast::print (ostream & out, int offset) const { out << "ROOT"; }

void Ast::shift (ostream & out, int offset) const {
    for (int i = 0; i < offset; i++) {
	out << " ";
    }
}

void Ast::registerFunctions () { }
void Ast::interpret () { }

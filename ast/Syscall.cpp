#include "Syscall.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Syscall::Syscall (string ident, vector<Ast*> * params, Position * pos) {
    this->ident = ident;
    this->params = params;
    this->pos = pos;
}

Syscall::~Syscall () {
    if (params) {
	for (int i = 0; i < params->size(); i++) {
	    delete (*params)[i];
	}
    }
}

void Syscall::interpret () {}

void Syscall::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "syscall " << ident << " (";
    for (int i = 0; i < params->size(); i++) {
	(*params)[i]->print (out);
    }
    out << ")";
}

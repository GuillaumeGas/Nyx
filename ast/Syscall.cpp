#include "Syscall.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Syscall::Syscall (string ident, vector<Expression*> * params, Position * pos) {
    this->ident = ident;
    this->params = params;
    this->pos = pos;
}

Syscall::~Syscall () {
    if (params) {
	for (auto it : *params) {
	    delete *it;
	}
    }
}

void Syscall::interpret () {
    if (ident == "print") {
	sysPrint ();
    } else if (ident == "println") {
	sysPrintln ();
    } else {
	throw SemanticErrorException ("Unknown syscall !", pos);
    }
}

void Syscall::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "syscall<" << ident << "> (";
    if (params != NULL) {
	int i = 0;
	for (auto it : *params) {
	    it->print (out);
	    if (i < params->size () - 1)
		out << ", ";
	    ++i;
	}
    }
    out << ")";
}

void Syscall::_sysPrint (Expression * e) {
    switch (e->getType ()->value) {
    case TYPE::INT:
	cout << e->getValue ()->getInt ();
	break;
    case TYPE::CHAR:
	cout << e->getValue ()->getChar ();
	break;
    case TYPE::STRING:
	cout << *((string*)(e->getValue ()->getPtr ()));
	break;
    default:
	SemanticErrorException ("Unknown type !", pos);
    }
}

void Syscall::sysPrint () {
    for (auto it : *params) {
	Expression * e = it->interpretExpression ();
	_sysPrint (e);
    }
}

void Syscall::sysPrintln () {
    for (auto it : *params) {
	Expression * e = it->interpretExpression ();
	_sysPrint (e);
	cout << endl;
    }
}

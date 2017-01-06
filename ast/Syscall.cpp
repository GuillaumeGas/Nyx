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
    	delete params;
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

void Syscall::_sysPrint (Value & v) {
    switch (v.getType ()->value) {
    case TYPE::INT:
	cout << v.getInt ();
	break;
    case TYPE::CHAR:
	cout << v.getChar ();
	break;
    // case TYPE::STRING:
    // 	cout << *((string*)(v.getValue ()->getPtr ()));
    // 	break;
    default:
	SemanticErrorException ("Unknown type !", pos);
    }
}

void Syscall::sysPrint () {
    for (auto it : *params) {
	Value v = it->interpretExpression ();
	_sysPrint (v);
    }
}

void Syscall::sysPrintln () {
    for (auto it : *params) {
	Value v = it->interpretExpression ();
	_sysPrint (v);
	cout << endl;
    }
}

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
	for (int i = 0; i < params->size(); i++) {
	    delete (*params)[i];
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
	for (int i = 0; i < params->size(); i++) {
	    (*params)[i]->print (out);
	    if (i < params->size()-1)
		out << ", ";
	}
    }
    out << ")";
}

void Syscall::_sysPrint (Expression * e) {
    vector<Expression*> * vec;
    switch (e->getType ()->value) {
    case TYPE::INT:
	cout << e->getValue ()->Int;
	break;
    case TYPE::CHAR:
	cout << e->getValue ()->Char;
	break;
    case TYPE::FLOAT:
	cout << e->getValue ()->Float;
	break;
    case TYPE::STRING:
	vec = ((String*)e)->array;
	for (auto it : *vec) {
	    char c = it->getValue ()->Char;
	    cout << c;
	}
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

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
	for (auto it : *params)
	    if (it) {
		delete it;
	    }
    	delete params;
    }
}

void Syscall::secondPass () {
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

void Syscall::_sysPrint (AbstractObject * e) {
    vector<Expression*> * vec = NULL;
    Range * range = NULL;

    if (e->getType ()->value == TYPE::ARRAY || e->getType ()->value == TYPE::RANGE)
	cout << "[";

    switch (e->getType ()->value) {
    case TYPE::INT:
	cout << e->getInt ();
	break;
    case TYPE::CHAR:
	cout << e->getChar ();
	break;
    case TYPE::BOOL:
	cout << e->getBool ();
	break;
    case TYPE::FLOAT:
	cout << e->getFloat ();
	break;
    case TYPE::STRING:
	vec = e->getArray ();
	for (auto it : *vec) {
	    _sysPrint ((AbstractObject*) it);
	}
	break;
    case TYPE::ARRAY:
	vec = e->getArray ();
	for (int i = 0; i < vec->size (); i++) {
	    AbstractObject * obj = (*vec)[i]->interpretExpression ();
	    _sysPrint (obj);
	    if (i < vec->size () - 1)
		cout << ", ";
	}
	break;
    case TYPE::RANGE:
	cout << e->getRangeStart ()->getInt ();
	cout << " .. ";
	cout << e->getRangeEnd ()->getInt ();
	break;
    default:
	SemanticErrorException ("Unknown type " + e->getType ()->toString () + "!", pos);
    }

    if (e->getType ()->value == TYPE::ARRAY || e->getType ()->value == TYPE::RANGE)
	cout << "]";
}

void Syscall::sysPrint () {
    for (auto it : *params) {
	_sysPrint (it->interpretExpression ());
    }
}

void Syscall::sysPrintln () {
    for (auto it : *params) {
	_sysPrint (it->interpretExpression ());
    }
    cout << endl;
}

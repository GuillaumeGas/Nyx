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

void Syscall::_sysPrint (Expression * e) {
    vector<Expression*> * vec = NULL;
    Range * range = NULL;

    Value * v = e->getValue ();

    if (v->getType ()->value == TYPE::ARRAY || v->getType ()->value == TYPE::RANGE)
	cout << "[";

    switch (v->getType ()->value) {
    case TYPE::INT:
	cout << v->getInt ();
	break;
    case TYPE::CHAR:
	cout << v->getChar ();
	break;
    case TYPE::FLOAT:
	cout << v->getFloat ();
	break;
    case TYPE::STRING:
	vec = ((String*)(v->getPtr ()))->array;
	for (auto it : *vec) {
	    char c = it->getValue ()->getChar ();
	    cout << c;
	}
	break;
    case TYPE::ARRAY:
	vec = ((Array*)(v->getPtr ()))->array;
	for (int i = 0; i < vec->size (); i++) {
	    _sysPrint ((*vec)[i]);
	    if (i < vec->size () - 1)
		cout << ", ";
	}
	break;
    case TYPE::RANGE:
	range = (Range*) v->getPtr ();
	cout << range->start->getValue ()->getInt ();
	cout << " .. ";
	cout << range->end->getValue ()->getInt ();
	break;
    default:
	SemanticErrorException ("Unknown type !", pos);
    }

    if (v->getType ()->value == TYPE::ARRAY || v->getType ()->value == TYPE::RANGE)
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
	cout << endl;
    }
    cout << endl;
}

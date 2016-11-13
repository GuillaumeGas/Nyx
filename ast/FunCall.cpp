#include "FunCall.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

FunCall::FunCall (string name, vector<Expression*> * params, Position * pos) {
    this->name = name;
    this->params = params;
    this->pos = pos;
}

FunCall::~FunCall () {
    if (params) {
	for (int i = 0; i < params->size(); i++) {
	    delete (*params)[i];
	}
    }
}

void FunCall::interpret () {}

void FunCall::print (ostream & out, int offset) const {
    shift (out, offset);
    out << name << " (";
    for (int i = 0; i < params->size(); i++) {
	(*params)[i]->print (out, offset);
	if (i < params->size()-1)
	    out << ", ";
    }
    out << ")";
}

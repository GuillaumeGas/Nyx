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
	for (auto it : *params)
	    if (it) delete it;
	delete params;
    }
}

void FunCall::interpret () {}

void FunCall::print (ostream & out, int offset) const {
    shift (out, offset);
    out << name << " (";
    if (params != NULL) {
	for (int i = 0; i < params->size(); i++) {
	    (*params)[i]->print (out);
	    if (i < params->size()-1)
		out << ", ";
	}
    }
    out << ")";
}

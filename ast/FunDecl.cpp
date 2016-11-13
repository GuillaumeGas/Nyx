#include "FunDecl.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

FunDecl::FunDecl (Type * type, string ident, vector<VarDecl*> * params, Bloc * content, Position * pos) {
    this->type = type;
    this->name = ident;
    this->params = params;
    this->content = content;
    this->pos = pos;
}

FunDecl::~FunDecl () {
    if (type)
	delete type;
    if (params) {
	for (int i = 0; i < params->size(); i++)
	    delete (*params)[i];
    }
    if (content)
	delete content;
}

void FunDecl::interpret () { }

void FunDecl::print (ostream & out, int offset) const {
    shift (out, offset);
    out << type->to_string() << " " << name << "(";
    if (params)
	for (int i = 0; i < params->size(); i++) {
	    (*params)[i]->print (out);
	    if (i < params->size()-1)
		out << ", ";
	}
    out << ") {" << endl;
    shift (out, offset);
    content->print (out, offset+INDENT);
    shift (out, offset);
    out << "}" << endl;
}

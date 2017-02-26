#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "FunDecl.hpp"
#include "Bloc.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

FunDecl::FunDecl (Type * type, const string & ident, vector<VarDecl*> * params, Bloc * content, Position * pos) {
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
	for (auto it : *params)
	    if (it) delete it;
	delete params;
    }
    if (content)
	delete content;
}

void FunDecl::registerFunctions () {
    symbol::Table * table = symbol::Table::getInstance ();
    table->addFunSymbol (new symbol::FunSymbol (name, this), pos);
}

void FunDecl::execute (vector<Expression*> * params) {
    symbol::Table * table = symbol::Table::getInstance ();

    if (this->params != NULL) {
	if (params == NULL || (params->size () != this->params->size ())) {
	    cout << "[!] Invalid parameters" << endl;
	    throw -1;
	}

	vector<AbstractObject*> obj_params;
	for (auto it : *params)
	    obj_params.push_back (it->interpretExpression ());

	table->enterBlock ();
				  
	for (int i = 0; i < params->size (); i++) {
	    VarDecl * param = (VarDecl*)(*(this->params))[i];
	    if (obj_params[i]->getType ()->value != param->type->value) {
		cout << "[!] Invalid param type !" << endl;
		throw -1;
	    }
	    table->addSymbol (new symbol::Symbol (param->var_id->name, obj_params[i]), param->pos);
	}
    } else {
	if (params != NULL) {
	    cout << "[!] Invalid parameter." << endl;
	    throw -1;
	}
	table->enterBlock ();
    }
	
    content->interpret ();

    table->exitBlock ();
}

void FunDecl::print (ostream & out, int offset) const {
    shift (out, offset);
    out << type->toString() << " " << name << "(";
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

#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "Function.hpp"
#include "Bloc.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Function::Function (Type * type, const string & ident, vector<VarDeclPtr> * params, BlocPtr content, Position * pos) {
    this->type = type;
    this->name = ident;
    this->params = params;
    this->content = content;
    this->pos = pos;
}

Function::~Function () {
    if (type)
	delete type;
    if (params)
	delete params;
}

void Function::registerFunctions () {
    symbol::Table * table = symbol::Table::getInstance ();
    table->addFunSymbol (new symbol::FunSymbol (name, this), pos);
}

ExpressionPtr Function::execute (vector<ExpressionPtr> * params) {
    // symbol::Table * table = symbol::Table::getInstance ();
    // table->enterFunBlock (this);

    // if (this->params != NULL) {
    // 	if (params == NULL || (params->size () != this->params->size ())) {
    // 	    cout << "[!] Invalid parameters" << endl;
    // 	    throw -1;
    // 	}

    // 	for (int i = 0; i < params->size (); i++) {
    // 	    VarDeclPtr param = this->params->at (i);
    // 	    ExpressionPtr value = params->at (i);
    // 	    if (value->getType ()->value != param->type->value) {
    // 		cout << "[!] Invalid param type !" << endl;
    // 		throw -1;
    // 	    }
    // 	    table->addSymbol (new symbol::Symbol (param->var_id->name, value), param->pos);
    // 	}
    // } else {
    // 	if (params != NULL) {
    // 	    cout << "[!] Invalid parameter." << endl;
    // 	    throw -1;
    // 	}
    // }
    
    // /* We interpret the content function while we don't meet a return statement */
    // vector<InstructionPtr> * vec_inst = this->content->content;
    // for (AstPtr a : *vec_inst)
    // 	a->registerFunctions ();

    // int i = 0;
    // int vec_size = vec_inst->size ();
    // while (i < vec_size && this->ret == NULL) {
    // 	(*vec_inst)[i]->interpret ();
    // 	i++;
    // }

    // table->exitFunBlock ();

    // return this->ret;
    return NullExpression ();
}

void Function::setRet (ExpressionPtr ret) {
    this->ret = ret;
}

void Function::print (ostream & out, int offset) const {
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

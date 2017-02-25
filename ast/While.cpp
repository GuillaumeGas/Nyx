#include "While.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

While::While (string * ident, Expression * expr, Bloc * bloc, Position * pos) {
    this->ident = ident;
    this->expr = expr;
    this->bloc = bloc;
    this->pos = pos;
}

While::~While () {
    if (ident)
	delete ident;
    if (expr)
	delete expr;
    if (bloc)
	delete bloc;
}

void While::secondPass () {
    symbol::Table * table = symbol::Table::getInstance ();
    table->enterBlock ();

    AbstractObject * expr_cond;
    TYPE expr_type;

    bool keep_going = true;
    while (keep_going) {
	expr_cond = expr->interpretExpression ();
	expr_type = expr_cond->getType ()->value;

    	if (expr_type == TYPE::INT) {
    	    keep_going = expr_cond->getInt ();
    	} else if (expr_type == TYPE::FLOAT) {
    	    keep_going = expr_cond->getFloat ();
    	} else if (expr_type == TYPE::CHAR) {
    	    keep_going = expr_cond->getChar ();
    	} else if (expr_type == TYPE::BOOL) {
    	    keep_going = expr_cond->getBool ();
    	} else {
    	    throw SemanticErrorException ("Expected boolean expression.", pos);
    	}

    	if (keep_going) {
	    table->enterBlock ();
	    bloc->secondPass ();
	    table->enterBlock ();
	}
    }
    
    if (expr_cond->getNbRef () <= 0)
	delete expr_cond;

    table->exitBlock ();
}

void While::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "While";
    if (ident)
	out << ":" << *ident;
    out << " (";
    expr->print (out);
    out << ") {" << endl;
    bloc->print (out, offset + INDENT);
    shift (out, offset);
    out << "}";
}

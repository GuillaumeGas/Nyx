#include "While.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

While::While (string * ident, ExpressionPtr expr, BlocPtr bloc, Position * pos) {
    this->ident = ident;
    this->expr = expr;
    this->bloc = bloc;
    this->pos = pos;
}

While::~While () {
    if (ident)
	delete ident;
}

void While::interpret () {
    symbol::Table * table = symbol::Table::getInstance ();
    table->enterBlock ();

    TYPE expr_type;

    bool keep_going = true;
    while (keep_going) {
    	expr = expr->interpretExpression ();
    	expr_type = expr->getType ()->value;

    	if (expr_type == TYPE::INT) {
    	    keep_going = expr->getInt ();
    	} else if (expr_type == TYPE::FLOAT) {
    	    keep_going = expr->getFloat ();
    	} else if (expr_type == TYPE::CHAR) {
    	    keep_going = expr->getChar ();
    	} else if (expr_type == TYPE::BOOL) {
    	    keep_going = expr->getBool ();
    	} else {
    	    throw SemanticErrorException ("Expected boolean expression.", pos);
    	}

    	if (keep_going) {
    	    table->enterBlock ();
    	    bloc->interpret ();
    	    table->enterBlock ();
    	}
    }
    

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

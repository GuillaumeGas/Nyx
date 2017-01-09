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

void While::interpret () {
    Expression * expr_cond = expr->interpretExpression ();
    Value * expr_value = expr_cond->getValue ();
    TYPE expr_type = expr_value->getType ()->value;
    symbol::Table * table = symbol::Table::getInstance ();

    table->enterBlock ();
    bool keep_going = true;
    while (keep_going) {
	expr = expr->interpretExpression ();
	Value * expr_value = expr->getValue ();
	TYPE expr_type = expr_value->getType ()->value;

	if (expr_type == TYPE::INT) {
	    keep_going = expr_value->getInt ();
	} else if (expr_type == TYPE::FLOAT) {
	    keep_going = expr_value->getFloat ();
	} else if (expr_type == TYPE::CHAR) {
	    keep_going = expr_value->getChar ();
	} else if (expr_type == TYPE::BOOL) {
	    keep_going = expr_value->getBool ();
	} else {
	    throw SemanticErrorException ("Expected boolean expression.", pos);
	}

	if (!keep_going)
	    break;

	bloc->interpret ();
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

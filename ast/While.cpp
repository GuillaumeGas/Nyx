#include "While.hpp"

using namespace std;
using namespace bob;
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

void While::interpret () {}

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

#include "While.hpp"

using namespace std;
using namespace bob;
using namespace ast;

While::While (Expression * expr, Bloc * bloc, Position * pos) {
    this->expr = expr;
    this->bloc = bloc;
    this->pos = pos;
}

While::~While () {
    if (expr)
	delete expr;
    if (bloc)
	delete bloc;
}

void While::interpret () {}

void While::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "While (";
    expr->print (out);
    out << ") {" << endl;
    bloc->print (out, offset + INDENT);
    shift (out, offset);
    out << "}";
}

#include "For.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

For::For (string * ident, VarId * var_loop, Expression * start_value, Expression * end_value, Bloc * bloc, Position * pos) {
    this->ident = ident;
    this->var_loop = var_loop;
    this->start_value = start_value;
    this->end_value = end_value;
    this->array = NULL;
    this->bloc = bloc;
    this->pos = pos;
}

For::For (string * ident, VarId * var_loop, Expression * array, Bloc * bloc, Position * pos) {
    this->ident = ident;
    this->var_loop = var_loop;
    this->start_value = NULL;
    this->end_value = NULL;
    this->array = array;
    this->bloc = bloc;
    this->pos = pos;
}

For::~For () {
    if (ident)
	delete ident;
    if (var_loop)
	delete var_loop;
    if (start_value)
	delete start_value;
    if (end_value)
	delete end_value;
    if (array)
	delete array;
    if (bloc)
	delete bloc;
}

void For::interpret() {}

void For::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "For";
    if (ident)
	out << ":" << *ident;
    out << " (";
    var_loop->print (out);
    out << " in ";
    if (array) {
	array->print (out);
    } else {
	start_value->print (out);
	out << " .. ";
	end_value->print (out);
    }
    out << ") {" << endl;
    bloc->print (out, offset+INDENT);
    shift (out, offset);
    out << "}";
}

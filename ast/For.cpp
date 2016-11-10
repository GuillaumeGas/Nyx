#include "For.hpp"

using namespace std;
using namespace bob;
using namespace ast;

For::For (VarId * var_loop, ConstInt * start_value, ConstInt * end_value, Bloc * bloc, Position * pos) {
    this->var_loop = var_loop;
    this->start_value = start_value;
    this->end_value = end_value;
    this->bloc = bloc;
    this->pos = pos;
}

For::~For () {
    if (var_loop)
	delete var_loop;
    if (start_value)
	delete start_value;
    if (end_value)
	delete end_value;
    if (bloc)
	delete bloc;
}

void For::interpret() {}

void For::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "For (";
    var_loop->print (out);
    out << " in ";
    start_value->print (out);
    out << " .. ";
    end_value->print (out);
    out << ") {" << endl;
    bloc->print (out, offset+1);
    shift (out, offset);
    out << "}" << endl;
}

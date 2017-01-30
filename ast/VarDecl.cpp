#include "VarDecl.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarDecl::VarDecl (VarId * var_id, Position * pos) : type (new Type ("undef")), var_id (var_id) {
    this->pos = pos;
}

VarDecl::VarDecl(Type * type, VarId * var_id, Position * pos) : type(type), var_id (var_id) {
    this->pos = pos;
}

VarDecl::~VarDecl() {
    if (type) {
	delete type;
    }
    if (var_id)
	delete var_id;
}

void VarDecl::interpret() {
    symbol::Table * table = symbol::Table::getInstance();
    table->addSymbol(new symbol::Symbol(var_id->name), pos);
}

void VarDecl::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "VarDecl ";
    var_id->print (out);
}

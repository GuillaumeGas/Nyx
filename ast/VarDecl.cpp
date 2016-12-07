#include "VarDecl.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarDecl::VarDecl(Type * type, VarId * var_id, Position * pos) : type(type), var_id (var_id) {
    this->pos = pos;
}

VarDecl::~VarDecl() {
    if (type) {
	delete type;
    }
}

void VarDecl::interpret() {
    // symbol::Table * table = symbol::Table::getInstance();
    // table->addSymbol(new symbol::Symbol(name, type), pos);
}

void VarDecl::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "VarDecl " << type->toString() << " ";
    var_id->print (cout);
}

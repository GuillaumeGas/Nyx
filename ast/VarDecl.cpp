#include "VarDecl.hpp"

using namespace std;
using namespace bob;
using namespace ast;

VarDecl::VarDecl(Type * type, string name, Position * pos) : type(type), name(name) {
    this->pos = pos;
}

VarDecl::~VarDecl() {
    if (type) {
	delete type;
    }
}

void VarDecl::interpret() {
    symbol::Table * table = symbol::Table::get_instance();
    table->add_symbol(new symbol::Symbol(name, type), pos);
}

void VarDecl::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "VarDecl " << type->to_string() << " " << name;
}

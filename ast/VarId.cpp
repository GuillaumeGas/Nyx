#include "VarId.hpp"

using namespace std;
using namespace bob;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
  this->pos = pos;
}

VarId::~VarId() {}

Expression * VarId::interpret_expr() {
    this->type = get_type();
    return this;
}

string VarId::to_string() const {
  return name;
}

Value * VarId::get_value() const {
    // symbol::Table * table = symbol::Table::get_instance();

    // symbol::Symbol * s = table->get_symbol (name, pos);
    // switch (this->type->get_type()) {
    // case TYPE::INT:
    // 	this->value.Int = s->
    // }
}

Type * VarId::get_type() const {
    symbol::Table * table = symbol::Table::get_instance();

    symbol::Symbol * s = table->get_symbol (name, pos);
    return s->get_type();
}

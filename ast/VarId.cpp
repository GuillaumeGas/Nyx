#include "VarId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
  this->pos = pos;
}

VarId::~VarId() {}

Expression * VarId::interpretExpr() {
    this->type = getType();
    return this;
}

void VarId::print (ostream & out, int offset) const {
    out << name;
}

Value * VarId::getValue() const {
    // symbol::Table * table = symbol::Table::getInstance();

    // symbol::Symbol * s = table->getSymbol (name, pos);
    // switch (this->type->getType()) {
    // case TYPE::INT:
    // 	this->value.Int = s->
    // }
}

Type * VarId::getType() const {
    symbol::Table * table = symbol::Table::getInstance();

    symbol::Symbol * s = table->getSymbol (name, pos);
    return s->getType();
}

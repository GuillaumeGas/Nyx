#include "VarId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
  this->pos = pos;
}

VarId::~VarId() {}

void VarId::print (ostream & out, int offset) const {
    out << name;
}

Type * VarId::getType () const {
    symbol::Table * table = symbol::Table::getInstance();

    symbol::Symbol * s = table->getSymbol (name, pos);
    return s->getType ();
}

Value * VarId::getValue () const {
    symbol::Table * table = symbol::Table::getInstance ();

    symbol::Symbol * s = table->getSymbol (name, pos);
    return s->getValue ();
}

Expression * VarId::interpretExpression () { return this; }

Expression * VarId::interpretPlus (Expression * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    Type * this_type = symbol->getType ();
    Type * e_type = e->getType ();

    if (this_type->value != e_type->value)
	throw TypeErrorException (this, e, pos);

    switch (this_type->value) {
    case TYPE::INT:
	return new Int (symbol->value->getInt () + e->getValue ()->getInt (), new Position (*pos));
    case TYPE::FLOAT:
	return new Float (symbol->value->getFloat () + e->getValue ()->getFloat (), new Position (*pos));
    case TYPE::CHAR:
	return new Char (symbol->value->getChar () + e->getValue ()->getChar (), new Position (*pos));
    // case TYPE::STRING:
    // 	return new String (new string (*((string*)symbol->value->getPtr ()) + *(e->getValue ()->getPtr ())), new Position (*pos));
    default:
	throw SemanticErrorException ("Type unexpected.", pos);
    }
}

Expression * VarId::interpretMinus (Expression * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    Type * this_type = symbol->getType ();
    Type * e_type = e->getType ();

    if (this_type->value != e_type->value)
	throw TypeErrorException (this, e, pos);

    switch (this_type->value) {
    case TYPE::INT:
	return new Int (symbol->value->getInt () - e->getValue ()->getInt (), new Position (*pos));
    case TYPE::FLOAT:
	return new Float (symbol->value->getFloat () - e->getValue ()->getFloat (), new Position (*pos));
    case TYPE::CHAR:
	return new Char (symbol->value->getChar () - e->getValue ()->getChar (), new Position (*pos));
    default:
	throw SemanticErrorException ("Type unexpected.", pos);
    }
}

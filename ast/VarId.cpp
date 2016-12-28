#include "VarId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
  this->pos = pos;
}

VarId::~VarId() {}

void VarId::print (ostream & out, int offset) const {
    out << "VarId " << name;
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

Expression * VarId::interpretPLUS (Expression * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    Type * this_type = symbol->getType ();
    Type * e_type = e->getType ();

    if (this_type->value != e_type->value)
	throw TypeErrorException (this, e, pos);

    switch (this_type->value) {
    case TYPE::INT:
	value->Int = symbol->value->Int + e->getValue ()->Int;
	break;
    case TYPE::FLOAT:
	value->Float = symbol->value->Float + e->getValue ()->Float;
	break;
    case TYPE::CHAR:
	value->Char = symbol->value->Char + e->getValue ()->Char;
	break;
    case TYPE::STRING:
	TODO_SEM ("VarId + String");
	break;
    case TYPE::ARRAY:
	TODO_SEM ("VarId + Array");
	break;
    default:
	throw SemanticErrorException ("Type unexpected.", pos);
    }
    return this;
}

Expression * VarId::interpretMINUS (Expression * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    Type * this_type = symbol->getType ();
    Type * e_type = e->getType ();

    if (this_type->value != e_type->value)
	throw TypeErrorException (this, e, pos);

    switch (this_type->value) {
    case TYPE::INT:
	return new Int (symbol->value->Int - e->getValue ()->Int, new Position (*pos));
    case TYPE::FLOAT:
	return new Float (symbol->value->Float - e->getValue ()->Float, new Position (*pos));
    case TYPE::CHAR:
	return new Char (symbol->value->Char - e->getValue ()->Char, new Position (*pos));
    default:
	throw SemanticErrorException ("Type unexpected.", pos);
    }
}

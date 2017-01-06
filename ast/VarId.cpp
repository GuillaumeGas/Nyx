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

Value VarId::interpretExpression () { return *(getValue ()); }

Value VarId::interpretPlus (Expression * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    Type * this_type = symbol->getType ();
    Type * e_type = e->getValue ()->getType ();

    if (this_type->value != e_type->value)
	throw TypeErrorException (this, e, pos);

    switch (this_type->value) {
    case TYPE::INT:
	return Value (symbol->value->getInt () + e->getValue ()->getInt ());
    case TYPE::FLOAT:
	return Value (symbol->value->getFloat () + e->getValue ()->getFloat ());
    case TYPE::CHAR:
	return Value (symbol->value->getChar () + e->getValue ()->getChar ());
    // case TYPE::STRING:
    // 	return new String (new string (*((string*)symbol->value->getPtr ()) + *(e->getValue ()->getPtr ())), new Position (*pos));
    default:
	throw SemanticErrorException ("Type unexpected.", pos);
    }
}

Value VarId::interpretAssign (Expression * e) {
    Value res = e->interpretExpression ();

    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    switch (res.getType ()->value) {
    case TYPE::INT:
	symbol->setValue (res.getInt ());
	break;
    case TYPE::FLOAT:
	symbol->setValue (res.getFloat ());
	break;
    case TYPE::CHAR:
	symbol->setValue (res.getChar ());
	break;
    case TYPE::BOOL:
	symbol->setValue (res.getBool ());
	break;
    default:
	throw SemanticErrorException ("Undefined Type !", pos);
    }

    return *(symbol->getValue ());
}


// Expression * VarId::interpretMinus (Expression * e) {
//     symbol::Table * table = symbol::Table::getInstance ();
//     symbol::Symbol * symbol = table->getSymbol (name, pos);

//     Type * this_type = symbol->getType ();
//     Type * e_type = e->getType ();

//     if (this_type->value != e_type->value)
// 	throw TypeErrorException (this, e, pos);

//     switch (this_type->value) {
//     case TYPE::INT:
// 	return new Int (symbol->value->getInt () - e->getValue ()->getInt (), new Position (*pos));
//     case TYPE::FLOAT:
// 	return new Float (symbol->value->getFloat () - e->getValue ()->getFloat (), new Position (*pos));
//     case TYPE::CHAR:
// 	return new Char (symbol->value->getChar () - e->getValue ()->getChar (), new Position (*pos));
//     default:
// 	throw SemanticErrorException ("Type unexpected.", pos);
//     }
// }

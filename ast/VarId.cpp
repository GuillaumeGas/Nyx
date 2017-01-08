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

// Type * VarId::getType () const {
//     symbol::Table * table = symbol::Table::getInstance();

//     symbol::Symbol * s = table->getSymbol (name, pos);
//     return s->getType ();
// }

// Value * VarId::getValue () const {
//     symbol::Table * table = symbol::Table::getInstance ();

//     symbol::Symbol * s = table->getSymbol (name, pos);
//     return s->getValue ();
// }

Expression * VarId::interpretExpression () {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * s = table->getSymbol (name, pos);
    Value * symbol_value = s->getValue ();

    value = new Value (*symbol_value);

    return this;
}

Expression * VarId::interpretPLUS (Expression * e) {
    Type * this_type = value->getType ();
    Type * e_type = e->getValue ()->getType ();

    if (this_type->value != e_type->value)
	throw TypeErrorException (this, e, pos);

    switch (this_type->value) {
    case TYPE::INT:
	value->set (value->getInt () + e->getValue ()->getInt ());
	break;
    case TYPE::FLOAT:
	value->set (value->getFloat () + e->getValue ()->getFloat ());
	break;
    case TYPE::CHAR:
	value->set (value->getChar () + e->getValue ()->getChar ());
	break;
    default:
	throw SemanticErrorException ("Type unexpected.", pos);
    }

    return this;
}

// Expression * VarId::interpretMINUS (Expression * e) {
//     symbol::Table * table = symbol::Table::getInstance ();
//     symbol::Symbol * symbol = table->getSymbol (name, pos);

//     Type * this_type = getType ();
//     Type * e_type = e->getValue ()->getType ();

//     if (this_type->value != e_type->value)
// 	throw TypeErrorException (this, e, pos);

//     switch (this_type->value) {
//     case TYPE::INT:
// 	return Value (value->getInt () - e->getValue ()->getInt ());
//     case TYPE::FLOAT:
// 	return Value (value->getFloat () - e->getValue ()->getFloat ());
//     case TYPE::CHAR:
// 	return Value (value->getChar () - e->getValue ()->getChar ());
//     default:
// 	throw SemanticErrorException ("Type unexpected.", pos);
//     }
// }


Expression * VarId::interpretASSIGN (Expression * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    Value * res = e->getValue ();

    switch (res->getType ()->value) {
    case TYPE::INT:
	symbol->setValue (res->getInt ());
	value->set (res->getInt ());
	break;
    case TYPE::FLOAT:
	symbol->setValue (res->getFloat ());
	value->set (res->getFloat ());
	break;
    case TYPE::CHAR:
	symbol->setValue (res->getChar ());
	value->set (res->getChar ());
	break;
    case TYPE::BOOL:
	symbol->setValue (res->getBool ());
	value->set (res->getBool ());
	break;
    default:
	throw SemanticErrorException ("Undefined Type ! " + res->getType ()->toString(), pos);
    }

    return this;
}

Expression * VarId::interpretUnaryMINUS () {
    Type * this_type = value->getType ();

    if (this_type->value != TYPE::INT && this_type->value != TYPE::FLOAT)
	throw SemanticErrorException ("Bad operand type for unary '-' : " + value->getType ()->toString(), pos);

    if (this_type->value == TYPE::INT) {
	value->set (value->getInt () * -1);
    } else if (this_type->value == TYPE::FLOAT) {
	value->set (value->getFloat () * -1);
    } else {
	TODO_SEM ("UnOp VarId type");
    }

    return this;
}

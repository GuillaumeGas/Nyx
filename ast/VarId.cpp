#include "VarId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
    this->pos = pos;
}

VarId::VarId (string name, AbstractObject * ptr, Position * pos) : name (name), value (ptr) {
    this->pos = pos;
}

VarId::~VarId() {}

bool VarId::getBool () const { return value->getBool (); }
int VarId::getInt () const { return value->getInt (); }
char VarId::getChar () const { return value->getChar (); }
float VarId::getFloat () const { return value->getFloat (); }
vector<Expression*> * VarId::getArray () const { return value->getArray (); }
AbstractObject * VarId::getRangeStart () const { return value->getRangeStart (); }
AbstractObject * VarId::getRangeEnd () const { return value->getRangeEnd (); }

void VarId::print (ostream & out, int offset) const {
    out << "VarId " << name;
}

Expression * VarId::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new VarId (name, value, new_pos);
}

AbstractObject * VarId::getPtr () {
    return value;
}

AbstractObject * VarId::interpretExpression () {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    if (symbol->isDef ()) {
	value = symbol->getValue ();
	type = new Type (*(value->getType ()));
    }

    return this;
}

AbstractObject * VarId::interpretASSIGN (AbstractObject * e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    // if is not undef, we update the number of ref on the referenced object,
    // and we check if the value referenced by this var needs to be destroyed
    if (symbol->isDef ()) {
	AbstractObject * object = symbol->getValue ();
	object->setNbRef (object->getNbRef () - 1);
    }

    // This object is referenced one more time by the current var...
    // e = e->interpretExpression ();
    AbstractObject * new_value = e->getPtr ();
    new_value->setNbRef (new_value->getNbRef () + 1);

    // The var now references to the new object !
    symbol->setValue (new_value);

    return new_value;
}

AbstractObject * VarId::interpretLE (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("<="), e);
}

AbstractObject * VarId::interpretGE (AbstractObject * e) {
    return _interpretBinop (Operator::getValue (">="), e);
}
AbstractObject * VarId::interpretNE (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("!="), e);
}
AbstractObject * VarId::interpretLT (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("<"), e);
}
AbstractObject * VarId::interpretGT (AbstractObject * e) {
    return _interpretBinop (Operator::getValue (">"), e);
}
AbstractObject * VarId::interpretEQ (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("=="), e);
}
AbstractObject * VarId::interpretAND (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("&&"), e);
}
AbstractObject * VarId::interpretOR (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("||"), e);
}
AbstractObject * VarId::interpretPLUS (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("+"), e);
}

AbstractObject * VarId::interpretMINUS (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("-"), e);
}
AbstractObject * VarId::interpretMUL (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("*"), e);
}
AbstractObject * VarId::interpretDIV (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("/"), e);
}
AbstractObject * VarId::interpretMOD (AbstractObject * e) {
    return _interpretBinop (Operator::getValue ("%"), e);
}

AbstractObject * VarId::interpretUnaryMINUS () {
    if (value->getType ()->value != TYPE::INT && value->getType ()->value != TYPE::FLOAT)
	throw SemanticErrorException ("Bad operand type for unary '-' : " + value->getType ()->toString(), pos);

    if (value->getType ()->value == TYPE::INT) {
	return new Int (value->getInt () * -1, NULL);
    } else if (value->getType ()->value == TYPE::FLOAT) {
	return new Float (value->getFloat () * -1, NULL);
    } else {
	TODO_SEM ("UnOp VarId type");
    }
}

AbstractObject * VarId::_interpretBinop (Op op, AbstractObject * e) {
    switch (op) {
    case Op::PLUS:
	return value->interpretPLUS (e);
    case Op::MINUS:
	return value->interpretMINUS (e);
    case Op::MUL:
	return value->interpretMUL (e);
    case Op::DIV:
	return value->interpretDIV (e);
    case Op::MOD:
	return value->interpretMOD (e);
    case Op::LT:
	return value->interpretLT (e);
    case Op::LE:
	return value->interpretLE (e);
    case Op::GT:
	return value->interpretGT (e);
    case Op::GE:
	return value->interpretGE (e);
    case Op::EQ:
	return value->interpretEQ (e);
    case Op::NE:
	return value->interpretNE (e);
    case Op::AND:
	return value->interpretAND (e);
    case Op::OR:
	return value->interpretOR (e);
    default:
	throw SemanticErrorException ("Unknown Operator !", pos);
    }
}

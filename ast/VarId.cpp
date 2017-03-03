#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "VarId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
    this->pos = pos;
    this->type = NULL;
}

VarId::VarId (string name, ExpressionPtr ptr, Position * pos) : name (name), value (ptr) {
    this->pos = pos;
    this->type = NULL;
}

VarId::~VarId() {}

bool VarId::getBool () const { return value->getBool (); }
int VarId::getInt () const { return value->getInt (); }
char VarId::getChar () const { return value->getChar (); }
float VarId::getFloat () const { return value->getFloat (); }
vector<ExpressionPtr> * VarId::getArray () const { return value->getArray (); }
ExpressionPtr VarId::getRangeBegin () const { return value->getRangeBegin (); }
ExpressionPtr VarId::getRangeEnd () const { return value->getRangeEnd (); }

void VarId::print (ostream & out, int offset) const {
    out << "VarId " << name;
}

ExpressionPtr VarId::clone () {
    return value->clone ();
}

ExpressionPtr VarId::interpretExpression () {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    if (symbol->isDef ()) {
	value = symbol->getValue ();
	type = new Type (*(value->getType ()));
    }

    return shared_from_this ();
}

ExpressionPtr VarId::interpretASSIGN (ExpressionPtr e) {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (name, pos);

    symbol->setValue (e->interpretExpression ());

    return shared_from_this ();
}

ExpressionPtr VarId::interpretLE (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("<="), e);
}

ExpressionPtr VarId::interpretGE (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue (">="), e);
}
ExpressionPtr VarId::interpretNE (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("!="), e);
}
ExpressionPtr VarId::interpretLT (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("<"), e);
}
ExpressionPtr VarId::interpretGT (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue (">"), e);
}
ExpressionPtr VarId::interpretEQ (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("=="), e);
}
ExpressionPtr VarId::interpretAND (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("&&"), e);
}
ExpressionPtr VarId::interpretOR (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("||"), e);
}
ExpressionPtr VarId::interpretPLUS (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("+"), e);
}
ExpressionPtr VarId::interpretMINUS (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("-"), e);
}
ExpressionPtr VarId::interpretMUL (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("*"), e);
}
ExpressionPtr VarId::interpretDIV (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("/"), e);
}
ExpressionPtr VarId::interpretMOD (ExpressionPtr e) {
    return _interpretBinop (Operator::getValue ("%"), e);
}

ExpressionPtr VarId::interpretUnaryMINUS () {
    if (value->getType ()->value != TYPE::INT && value->getType ()->value != TYPE::FLOAT)
	throw SemanticErrorException ("Bad operand type for unary '-' : " + value->getType ()->toString(), pos);

    if (value->getType ()->value == TYPE::INT) {
	return Expression::New<Int> (value->getInt () * -1, NULL_POSITION);
    } else if (value->getType ()->value == TYPE::FLOAT) {
	return Expression::New<Float> (value->getFloat () * -1, NULL_POSITION);
    } else {
	TODO_SEM ("UnOp VarId type");
    }
}

ExpressionPtr VarId::_interpretBinop (Op op, ExpressionPtr e) {
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

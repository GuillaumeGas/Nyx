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

Expression * VarId::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    interpretExpression ();
    VarId * new_varId = new VarId (name, new_pos);
    new_varId->interpretExpression ();
}

Expression * VarId::interpretExpression () {
    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * s = table->getSymbol (name, pos);
    Value * symbol_value = s->getValue ();

    value = new Value (*symbol_value);

    return this;
}

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
    case TYPE::PTR:
	symbol->setValue (res->getPtr ());
	value->set (res->getPtr ());
	break;
    case TYPE::ARRAY:
	symbol->setValue (res->getPtr (), "array");
	value->set (res->getPtr (), "array");
	break;
    case TYPE::STRING:
	symbol->setValue (res->getPtr (), "string");
	value->set (res->getPtr (), "string");
	break;
    case TYPE::RANGE:
	symbol->setValue (res->getPtr (), "range");
	value->set (res->getPtr (), "range");
	break;
    default:
	throw SemanticErrorException ("Undefined Type ! " + res->getType ()->toString(), pos);
    }

    return this;
}

Expression * VarId::interpretLE (Expression * e) {
    return _interpretBinop (Operator::getValue ("<="), e);
}

Expression * VarId::interpretGE (Expression * e) {
    return _interpretBinop (Operator::getValue (">="), e);
}
Expression * VarId::interpretNE (Expression * e) {
    return _interpretBinop (Operator::getValue ("!="), e);
}
Expression * VarId::interpretLT (Expression * e) {
    return _interpretBinop (Operator::getValue ("<"), e);
}
Expression * VarId::interpretGT (Expression * e) {
    return _interpretBinop (Operator::getValue (">"), e);
}
Expression * VarId::interpretEQ (Expression * e) {
    return _interpretBinop (Operator::getValue ("=="), e);
}
Expression * VarId::interpretAND (Expression * e) {
    return _interpretBinop (Operator::getValue ("&&"), e);
}
Expression * VarId::interpretOR (Expression * e) {
    return _interpretBinop (Operator::getValue ("||"), e);
}
Expression * VarId::interpretPLUS (Expression * e) {
    return _interpretBinop (Operator::getValue ("+"), e);
}

Expression * VarId::interpretMINUS (Expression * e) {
    return _interpretBinop (Operator::getValue ("-"), e);
}
Expression * VarId::interpretMUL (Expression * e) {
    return _interpretBinop (Operator::getValue ("*"), e);
}
Expression * VarId::interpretDIV (Expression * e) {
    return _interpretBinop (Operator::getValue ("/"), e);
}
Expression * VarId::interpretMOD (Expression * e) {
    return _interpretBinop (Operator::getValue ("%"), e);
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

Expression * VarId::_interpretBinop (Op op, Expression * e) {
    Type * type = value->getType ();

    Expression * expr;
    if (type->isBasic ()) {
	switch (type->value) {
	case TYPE::INT:
	    expr = new Int (value->getInt (), pos);
	    break;
	case TYPE::FLOAT:
	    expr = new Float (value->getFloat (), pos);
	    break;
	case TYPE::CHAR:
	    expr = new Char (value->getChar (), pos);
	    break;
	case TYPE::BOOL:
	    expr = new Bool (value->getBool (), pos);
	    break;
	default:
	    throw SemanticErrorException ("Your var must be initialized !", pos);
	}

	_interpretOp (op, expr, e);
	if (value)
	    delete value;
	value = new Value (*(expr->getValue ()));
	delete expr;
    } else {
	expr = value->getPtr ();
	_interpretOp (op, expr, e);
	if (value)
	    delete value;
	value = new Value (*(expr->getValue ()));
    }
    return this;
}

Expression * VarId::_interpretOp (Op op, Expression * e1, Expression * e2) {
    switch (op) {
    case Op::PLUS:
	return e1->interpretPLUS (e2);
    case Op::MINUS:
	return e1->interpretMINUS (e2);
    case Op::MUL:
	return e1->interpretMUL (e2);
    case Op::DIV:
	return e1->interpretDIV (e2);
    case Op::MOD:
	return e1->interpretMOD (e2);
    case Op::LT:
	return e1->interpretLT (e2);
    case Op::LE:
	return e1->interpretLE (e2);
    case Op::GT:
	return e1->interpretGT (e2);
    case Op::GE:
	return e1->interpretGE (e2);
    case Op::EQ:
	return e1->interpretEQ (e2);
    case Op::NE:
	return e1->interpretNE (e2);
    case Op::AND:
	return e1->interpretAND (e2);
    case Op::OR:
	return e1->interpretOR (e2);
    default:
	throw SemanticErrorException ("Unknown Operator !", pos);
    }
}

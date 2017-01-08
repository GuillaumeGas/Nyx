#include "Binop.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Binop::Binop(Expression * e1, Expression * e2, Operator * op, Position * pos) : e1(e1), e2(e2), op(op) {
    this->pos = pos;
    this->value = new Value (this);
}

Binop::~Binop() {
    if (e1)
	delete e1;
    if (e2)
	delete e2;
    if (op)
	delete op;
}

Expression * Binop::interpretExpression () {
    Expression * left = e1->interpretExpression ();
    Expression * right = e2->interpretExpression ();

    switch (op->value) {
    case Op::ASSIGN:
	return left->interpretASSIGN (right);
    case Op::LE:
	return left->interpretLE (right);
    case Op::GE:
	return left->interpretGE (right);
    case Op::NE:
	return left->interpretNE (right);
    case Op::PLUSEQ:
	return left->interpretPLUSEQ (right);
    case Op::MINUSEQ:
	return left->interpretMINUSEQ (right);
    case Op::MULEQ:
	return left->interpretMULEQ (right);
    case Op::DIVEQ:
	return left->interpretDIVEQ (right);
    case Op::MODEQ:
	return left->interpretMODEQ (right);
    case Op::LT:
	return left->interpretLT (right);
    case Op::GT:
	return left->interpretGT (right);
    case Op::EQ:
	return left->interpretEQ (right);
    case Op::AND:
	return left->interpretAND (right);
    case Op::OR:
	return left->interpretOR (right);
    case Op::PLUS:
	return left->interpretPLUS (right);
    case Op::MINUS:
	return left->interpretMINUS (right);
    case Op::MUL:
	return left->interpretMUL (right);
    case Op::DIV:
	return left->interpretDIV (right);
    case Op::MOD:
	return left->interpretMOD (right);
    case Op::POINT:
	return left->interpretPOINT (right);
    default:
	throw SemanticErrorException ("Unknown operator '" + op->toString () + "'", pos);
    }
}

void Binop::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "Binop(";
    e1->print (out);
    out << ", " << op->toString() << " , ";
    e2->print (out);
    out << ")";
}

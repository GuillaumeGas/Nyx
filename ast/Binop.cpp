#include "Binop.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Binop::Binop(Expression * e1, Expression * e2, Operator * op, Position * pos) : e1(e1), e2(e2), op(op) {
    this->pos = pos;
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
    e1 = e1->interpretExpression ();
    e2 = e2->interpretExpression ();

    switch (op->value) {
    case Op::ASSIGN:
	return e1->interpretASSIGN (e2);
    case Op::LE:
	return e1->interpretLE (e2);
    case Op::GE:
	return e1->interpretGE (e2);
    case Op::NE:
	return e1->interpretNE (e2);
    case Op::PLUSEQ:
	return e1->interpretPLUSEQ (e2);
    case Op::MINUSEQ:
	return e1->interpretMINUSEQ (e2);
    case Op::MULEQ:
	return e1->interpretMULEQ (e2);
    case Op::DIVEQ:
	return e1->interpretDIVEQ (e2);
    case Op::MODEQ:
	return e1->interpretMODEQ (e2);
    case Op::LT:
	return e1->interpretLT (e2);
    case Op::GT:
	return e1->interpretGT (e2);
    case Op::EQ:
	return e1->interpretEQ (e2);
    case Op::AND:
	return e1->interpretAND (e2);
    case Op::OR:
	return e1->interpretOR (e2);
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
    case Op::POINT:
	return e1->interpretPOINT (e2);
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

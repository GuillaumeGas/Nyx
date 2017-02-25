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

void Binop::secondPass () {
    interpretExpression ();
}

AbstractObject * Binop::interpretExpression () {
    AbstractObject * left = e1->interpretExpression ();
    AbstractObject * right = e2->interpretExpression ();

    AbstractObject * res = NULL;

    switch (op->value) {
    case Op::ASSIGN:
	res = left->interpretASSIGN (right);
	break;
    case Op::LE:
	res = left->interpretLE (right);
	break;
    case Op::GE:
	res = left->interpretGE (right);
	break;
    case Op::NE:
	res = left->interpretNE (right);
	break;
    case Op::PLUSEQ:
	res = left->interpretPLUSEQ (right);
	break;
    case Op::MINUSEQ:
	res = left->interpretMINUSEQ (right);
	break;
    case Op::MULEQ:
	res = left->interpretMULEQ (right);
	break;
    case Op::DIVEQ:
	res = left->interpretDIVEQ (right);
	break;
    case Op::MODEQ:
	res = left->interpretMODEQ (right);
	break;
    case Op::LT:
	res = left->interpretLT (right);
	break;
    case Op::GT:
	res = left->interpretGT (right);
	break;
    case Op::EQ:
	res = left->interpretEQ (right);
	break;
    case Op::AND:
	res = left->interpretAND (right);
	break;
    case Op::OR:
	res = left->interpretOR (right);
	break;
    case Op::PLUS:
	res = left->interpretPLUS (right);
	break;
    case Op::MINUS:
	res = left->interpretMINUS (right);
	break;
    case Op::MUL:
	res = left->interpretMUL (right);
	break;
    case Op::DIV:
	res = left->interpretDIV (right);
	break;
    case Op::MOD:
	res = left->interpretMOD (right);
	break;
    case Op::POINT:
	res = left->interpretPOINT (right);
	break;
    default:
	throw SemanticErrorException ("Unknown operator '" + op->toString () + "'", pos);
    }

    if (res->pos == NULL)
	res->pos = new Position (pos->line, pos->column);;

    return res;
}

void Binop::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "Binop(";
    e1->print (out);
    out << ", " << op->toString() << " , ";
    e2->print (out);
    out << ")";
}

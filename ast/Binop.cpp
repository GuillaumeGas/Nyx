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
    case Op::PLUS:
	return e1->interpretPlus (e2);
    case Op::MINUS:
	return e1->interpretMinus (e2);
    case Op::MUL:
	return e1->interpretMul (e2);
    case Op::DIV:
	return e1->interpretDiv (e2);
    case Op::MOD:
	return e1->interpretMod (e2);
    default:
	throw SemanticErrorException ("Unknown operator '" + op->toString () + "'", pos);
    }
}

void Binop::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "Binop(";
    e1->print (out);
    out << " " << op->toString() << " ";
    e2->print (out);
    out << ")";
}

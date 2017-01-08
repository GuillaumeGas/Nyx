#include "UnOp.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

UnOp::UnOp (Operator * op, Expression * expr, Position * pos) {
    this->pos = pos;
    this->op = op;
    this->expr = expr;
    this->value = new Value ();
}

UnOp::~UnOp () {
    if (op)
	delete op;
    if (expr)
	delete expr;
}

void UnOp::print (ostream & out, int offset) const {
    out << "UnOp(" << op->toString() << ", ";
    expr->print (out, offset);
    out << ")";
}

Expression * UnOp::interpretExpression () {
    switch (op->value) {
    case Op::MINUS:
	return expr->interpretUnaryMINUS ();
    default:
	throw SemanticErrorException ("Unknown unary operator !", pos);
    }
}

Expression * UnOp::interpretUnaryMINUS () {
    Value * v = expr->getValue ();
    switch (v->getType ()->value) {
    case TYPE::INT:
	value->set (v->getInt () * -1);
	return this;
    default:
	TODO_SEM ("interpretUnaryMINUS");
    }
}

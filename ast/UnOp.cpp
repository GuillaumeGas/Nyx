#include "UnOp.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

UnOp::UnOp (Operator * op, Expression * expr, Position * pos) {
    this->pos = pos;
    this->op = op;
    this->expr = expr;
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
    expr = expr->interpretExpression ();
    switch (op->value) {
    case Op::MINUS:
	return expr->interpretUnaryMINUS ();
    default:
	throw SemanticErrorException ("Unknown unary operator !", pos);
    }
}

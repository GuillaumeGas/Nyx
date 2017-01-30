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

AbstractObject * UnOp::interpretExpression () {
    AbstractObject * e = expr->interpretExpression ();
    AbstractObject * res = NULL;

    Position * new_pos = new Position (pos->line, pos->column);

    switch (op->value) {
    case Op::MINUS:
	res = e->interpretUnaryMINUS ();
	break;
    default:
	throw SemanticErrorException ("Unknown unary operator !", pos);
    }

    res->pos = new_pos;
    return res;
}

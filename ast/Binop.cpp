#include "Binop.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Binop::Binop(ExpressionPtr left, ExpressionPtr right, Operator * op, Position * pos) : Expression (pos) {
    _left = left;
    _right = right;
    _op = op;
}

Binop::~Binop() {
    if (_op)
	delete _op;
}

void Binop::interpret () {
    interpretExpression ();
}

ExpressionPtr Binop::interpretExpression () {
    ExpressionPtr left = _left->interpretExpression ();
    ExpressionPtr right = _right->interpretExpression ();

    ExpressionPtr res;

    switch (_op->value) {
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
    	throw SemanticErrorException ("Unknown operator '" + _op->toString () + "'", _pos);
    }

    if (res->getPos () == NULL)
    	res->setPos (new Position (_pos->line, _pos->column));

    return res;
}

void Binop::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "Binop(";
    _left->print (out);
    out << ", " << _op->toString() << " , ";
    _right->print (out);
    out << ")";
}

ExpressionPtr Binop::getLeft () const {
    return _left;
}

void Binop::setLeft (ExpressionPtr left) {
    _left = left;
}

ExpressionPtr Binop::getRight ()  const {
    return _right;
}

void Binop::setRight (ExpressionPtr right) {
    _right = right;
}

Operator * Binop::getOp () const {
    return _op;
}

void Binop::setOp (Operator * op) {
    if (_op)
	delete _op;
    _op = op;
}

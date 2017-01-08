#include "Expression.hpp"
#include "exceptions/SemanticException.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Expression::Expression () {}

Expression::~Expression() {
    if (value)
	delete value;
}

void Expression::interpret() {
    interpretExpression ();
}

Value * Expression::getValue () const {
    return value;
}

Expression * Expression::clone () { return NULL; }

Expression * Expression::interpretExpression () { return NULL; }
Expression * Expression::interpretASSIGN (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretLE (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretGE (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretNE (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretPLUSEQ (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretMINUSEQ (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretMULEQ (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretDIVEQ (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretMODEQ (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretLT (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretGT (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretEQ (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretAND (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretOR (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretPLUS (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretMINUS (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretMUL (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretDIV (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretMOD (Expression * e) { throw TypeErrorException (this, e, pos); }
Expression * Expression::interpretPOINT (Expression * e) { throw TypeErrorException (this, e, pos); }

Expression * Expression::interpretUnaryMINUS () { throw SemanticErrorException ("Bad operand type for unary '-' : " + this->value->getType ()->toString(), pos); }

#include "Expression.hpp"
#include "exceptions/SemanticException.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Expression::Expression(Position* pos) : Instruction(pos), _type(nullptr) {}

Expression::~Expression() {
    if (_type)
        delete _type;
}

void Expression::interpret() {
    interpretExpression();
}

ExpressionPtr Expression::interpretExpression(bool) {
    return shared_from_this();
}

Type* Expression::getType() const {
    return _type;
}

void Expression::setType(Type* type) {
    if (_type)
        delete _type;
    _type = type;
}

bool Expression::getBool() const { throw - 1; }
int Expression::getInt() const { throw - 1; }
char Expression::getChar() const { throw - 1; }
float Expression::getFloat() const { throw - 1; }
vector<ExpressionPtr>* Expression::getArray() const { throw - 1; }
ExpressionPtr Expression::getRangeBegin() const { throw - 1; }
ExpressionPtr Expression::getRangeEnd() const { throw - 1; }
// Object * Expression::getObject () const { throw -1; }

void Expression::setBool(bool v) { throw - 1; }
void Expression::setInt(int v) { throw - 1; }
void Expression::setChar(char v) { throw - 1; }
void Expression::setFloat(float v) { throw - 1; }
void Expression::setArray(std::vector<ExpressionPtr>* v) { throw - 1; }
void Expression::setRangeBegin(ExpressionPtr v) { throw - 1; }
void Expression::setRangeEnd(ExpressionPtr v) { throw - 1; }
// virtual void Expression::setObject (Object * v) { throw -1; }

ExpressionPtr Expression::clone() { return shared_from_this(); }

ExpressionPtr Expression::interpretASSIGN(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretLE(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretGE(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretNE(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretPLUSEQ(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretMINUSEQ(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretMULEQ(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretDIVEQ(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretMODEQ(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretLT(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretGT(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretEQ(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretAND(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretOR(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretPLUS(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretMINUS(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretMUL(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretDIV(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretMOD(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }
ExpressionPtr Expression::interpretPOINT(ExpressionPtr e) { throw TypeErrorException(shared_from_this(), e, _pos); }

ExpressionPtr Expression::interpretUnaryMINUS() { throw SemanticErrorException("Bad operand type for unary '-' : " + _type->toString(), _pos); }

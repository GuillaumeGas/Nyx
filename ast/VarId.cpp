#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "VarId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarId::VarId(string name, Position* pos) : Expression(pos) {
    _type = NULL;
    _name = name;
}

VarId::VarId(string name, Position* pos, ExpressionPtr value) : Expression(pos) {
    _type = NULL;
    _name = name;
    _value = value;
}

VarIdPtr VarId::New(string name, Position* pos) {
    return std::make_shared<VarId>(name, pos);
}

VarIdPtr VarId::New(string name, Position* pos, ExpressionPtr value) {
    return std::make_shared<VarId>(name, pos, value);
}

string VarId::getName() const {
    return _name;
}

void VarId::setName(const string name) {
    _name = name;
}

ExpressionPtr VarId::getValue() const {
    return _value;
}

void VarId::setValue(ExpressionPtr value) {
    _value = value;
}

bool VarId::getBool() const { return _value->getBool(); }
int VarId::getInt() const { return _value->getInt(); }
char VarId::getChar() const { return _value->getChar(); }
float VarId::getFloat() const { return _value->getFloat(); }
vector<ExpressionPtr>* VarId::getArray() const { return _value->getArray(); }
ExpressionPtr VarId::getRangeBegin() const { return _value->getRangeBegin(); }
ExpressionPtr VarId::getRangeEnd() const { return _value->getRangeEnd(); }

void VarId::print(ostream& out, int offset) const {
    out << "VarId " << _name;
}

void VarId::declare()
{
    symbol::Table* table = symbol::Table::getInstance();

    table->getSymbol(_name, _pos)->isUsed(true);
}

ExpressionPtr VarId::clone() {
    return _value->clone();
}

ExpressionPtr VarId::interpretExpression() {
    symbol::Table* table = symbol::Table::getInstance();
    symbol::Symbol* symbol = table->getSymbol(_name, _pos);

    if (symbol->isDef()) {
        _value = symbol->getValue();
        _type = new Type(*(_value->getType()));
    }

    return shared_from_this();
}

ExpressionPtr VarId::interpretASSIGN(ExpressionPtr e) {
    symbol::Table* table = symbol::Table::getInstance();
    symbol::Symbol* symbol = table->getSymbol(_name, _pos);

    symbol->setValue(e->interpretExpression()->clone());

    if (e->getType()->value == TYPE::STRUCT)
        symbol->setIsStruct(true);

    return shared_from_this();
}

ExpressionPtr VarId::interpretPOINT(ExpressionPtr e)
{
    symbol::Table* table = symbol::Table::getInstance();
    symbol::Symbol* symbol = table->getSymbol(_name, _pos);

    if (symbol == nullptr || !symbol->isStruct())
        throw SemanticErrorException("'" + _name + "' is not a struct", _pos);

    symbol::StructSymbol * structSymbol = (symbol::StructSymbol*)symbol;
    VarIdPtr member = PointerCast<VarId>(e);
    ExpressionPtr memberExpression = structSymbol->getMember(member->getName());

    if (memberExpression == nullptr)
        throw SemanticErrorException("'" + member->getName() + "' is not a member of '" + _name + "'", _pos);

    return memberExpression->interpretExpression();
}

ExpressionPtr VarId::interpretLE(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("<="), e);
}

ExpressionPtr VarId::interpretGE(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue(">="), e);
}
ExpressionPtr VarId::interpretNE(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("!="), e);
}
ExpressionPtr VarId::interpretLT(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("<"), e);
}
ExpressionPtr VarId::interpretGT(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue(">"), e);
}
ExpressionPtr VarId::interpretEQ(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("=="), e);
}
ExpressionPtr VarId::interpretAND(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("&&"), e);
}
ExpressionPtr VarId::interpretOR(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("||"), e);
}
ExpressionPtr VarId::interpretPLUS(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("+"), e);
}
ExpressionPtr VarId::interpretMINUS(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("-"), e);
}
ExpressionPtr VarId::interpretMUL(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("*"), e);
}
ExpressionPtr VarId::interpretDIV(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("/"), e);
}
ExpressionPtr VarId::interpretMOD(ExpressionPtr e) {
    return _interpretBinop(Operator::getValue("%"), e);
}

ExpressionPtr VarId::interpretUnaryMINUS() {
    if (_value->getType()->value != TYPE::INT && _value->getType()->value != TYPE::FLOAT)
        throw SemanticErrorException("Bad operand type for unary '-' : " + _value->getType()->toString(), _pos);

    if (_value->getType()->value == TYPE::INT) {
        return Expression::New<Int>(_value->getInt() * -1, NULL_POSITION_PTR);
    }
    else if (_value->getType()->value == TYPE::FLOAT) {
        return Expression::New<Float>(_value->getFloat() * -1, NULL_POSITION_PTR);
    }
    else {
        TODO_SEM("UnOp VarId type");
    }
}

ExpressionPtr VarId::_interpretBinop(Op op, ExpressionPtr e) {
    switch (op) {
    case Op::PLUS:
        return _value->interpretPLUS(e);
    case Op::MINUS:
        return _value->interpretMINUS(e);
    case Op::MUL:
        return _value->interpretMUL(e);
    case Op::DIV:
        return _value->interpretDIV(e);
    case Op::MOD:
        return _value->interpretMOD(e);
    case Op::LT:
        return _value->interpretLT(e);
    case Op::LE:
        return _value->interpretLE(e);
    case Op::GT:
        return _value->interpretGT(e);
    case Op::GE:
        return _value->interpretGE(e);
    case Op::EQ:
        return _value->interpretEQ(e);
    case Op::NE:
        return _value->interpretNE(e);
    case Op::AND:
        return _value->interpretAND(e);
    case Op::OR:
        return _value->interpretOR(e);
    default:
        throw SemanticErrorException("Unknown Operator !", _pos);
    }
}

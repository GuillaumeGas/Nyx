#include "While.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

While::While(string* ident, ExpressionPtr expr, BlocPtr bloc, Position* pos) : Instruction(pos) {
    _ident = ident;
    _expr = expr;
    _bloc = bloc;
}

While::~While() {
    if (_ident)
        delete _ident;
}

void While::interpret() {
    symbol::Table* table = symbol::Table::getInstance();
    table->enterBlock();

    TYPE exprType;

    bool keepGoing = true;
    while (keepGoing) {
        _expr = _expr->interpretExpression();
        exprType = _expr->getType()->value;

        if (exprType == TYPE::INT) {
            keepGoing = _expr->getInt();
        }
        else if (exprType == TYPE::FLOAT) {
            keepGoing = _expr->getFloat();
        }
        else if (exprType == TYPE::CHAR) {
            keepGoing = _expr->getChar();
        }
        else if (exprType == TYPE::BOOL) {
            keepGoing = _expr->getBool();
        }
        else {
            throw SemanticErrorException("Expected boolean expression.", _pos);
        }

        if (keepGoing) {
            table->enterBlock();
            _bloc->interpret();
            table->enterBlock();
        }
    }


    table->exitBlock();
}

void While::print(ostream& out, int offset) const {
    shift(out, offset);
    out << "While";
    if (_ident)
        out << ":" << *_ident;
    out << " (";
    _expr->print(out);
    out << ") {" << endl;
    _bloc->print(out, offset + INDENT);
    shift(out, offset);
    out << "}";
}

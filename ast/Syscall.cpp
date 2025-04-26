#include <iostream>

#include "Syscall.hpp"
#include "../symbol/Table.hpp"
#include "../debugger/Debugger.hpp"

using namespace std;
using namespace nyx;
using namespace ast;
using namespace debug;

Syscall::Syscall(string ident, vector<ExpressionPtr>* params, Position* pos) : Expression(pos) {
    _ident = ident;
    _params = params;

    this->setType(new Type("void", true));
}

void Syscall::declare() {
    symbol::Table* table = symbol::Table::getInstance();

    if (_params)
        for (auto it : *_params)
            it->declare();
}

Syscall::~Syscall() {
    if (_params)
        delete _params;
}

void Syscall::interpret() {
    interpretExpression();
}

ExpressionPtr Syscall::interpretExpression(bool)
{
    if (_ident == "print") {
        return sysPrint();
    }
    else if (_ident == "println") {
        return sysPrintln();
    }
    else if (_ident == "readInt") {
        return sysReadInt();
    }
    else if (_ident == "debugBreak") {
	return sysDebugBreak();
    }
    else {
        throw SemanticErrorException("Unknown syscall !", _pos);
    }
}

void Syscall::print(ostream& out, int offset) const {
    shift(out, offset);
    out << "syscall<" << _ident << "> (";
    if (_params != NULL) {
        int i = 0;
        for (auto it : *_params) {
            it->print(out);
            if (i < _params->size() - 1)
                out << ", ";
            ++i;
        }
    }
    out << ")";
}

void Syscall::_sysPrint(ExpressionPtr e) {
    vector<ExpressionPtr>* vec = NULL;
    RangePtr range;

    ostream & out = *(Global::getInstance()->ostream);

    if (e->getType()->value == TYPE::ARRAY || e->getType()->value == TYPE::RANGE)
        out << "[";

    switch (e->getType()->value) {
    case TYPE::INT:
        out << e->getInt();
        break;
    case TYPE::CHAR:
        out << e->getChar();
        break;
    case TYPE::BOOL:
        out << e->getBool();
        break;
    case TYPE::FLOAT:
        out << e->getFloat();
        break;
    case TYPE::STRING:
        vec = e->getArray();
        for (auto it : *vec) {
            _sysPrint(it);
        }
        break;
    case TYPE::ARRAY:
        vec = e->getArray();
        for (int i = 0; i < vec->size(); i++) {
            ExpressionPtr obj = (*vec)[i]->interpretExpression();
            _sysPrint(obj);
            if (i < vec->size() - 1)
                out << ", ";
        }
        break;
    case TYPE::RANGE:
        out << e->getRangeBegin()->getInt();
        out << " .. ";
        out << e->getRangeEnd()->getInt();
        break;
    default:
        SemanticErrorException("Unknown type " + e->getType()->toString() + "!", _pos);
    }

    if (e->getType()->value == TYPE::ARRAY || e->getType()->value == TYPE::RANGE)
        out << "]";
}

ExpressionPtr Syscall::sysPrint() {
    for (auto it : *_params) {
        _sysPrint(it->interpretExpression());
    }

    return NullExpression();
}

ExpressionPtr Syscall::sysPrintln() {
    ostream & out = *(Global::getInstance()->ostream);

    if (_params)
    {
        for (auto it : *_params) {
            _sysPrint(it->interpretExpression());
        }
    }

    out << endl;

    return NullExpression();
}

ExpressionPtr Syscall::sysReadInt() {
    int intInput;

#ifdef __linux__
    scanf("%d", &intInput);
#else
    scanf_s("%d", &intInput, sizeof(int));
#endif

    this->setType(new Type("int", true));

    return Expression::New<Int>(intInput, _pos);
}

ExpressionPtr Syscall::sysDebugBreak() {
    Debugger* debugger = Debugger::getInstance();

    debugger->debugBreak();

    return NullExpression();
}

std::string Syscall::getIdent() const {
    return _ident;
}

void Syscall::setIdent(const std::string& ident) {
    _ident = ident;
}

std::vector<ExpressionPtr>* Syscall::getParams() const {
    return _params;
}

void Syscall::setParams(std::vector<ExpressionPtr>* params) {
    _params = params;
}

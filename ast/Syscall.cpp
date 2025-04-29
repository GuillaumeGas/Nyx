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
    ExpressionPtr res = Global::getInstance()->syscallInterface->execute(_ident, _params);
    
    if (res)
    {
        this->setType(new Type(*res->getType()));
        if (res->getPos() == nullptr)
            res->setPos(new Position(*_pos));
    }
    
    return res;
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

#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "FunCall.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

FunCall::FunCall(string name, vector<ExpressionPtr>* params, Position* pos) : Expression(pos) {
    _name = name;
    _params = params;
    _pos = pos;
}

FunCall::~FunCall() {
    if (_params)
        delete _params;
}

void FunCall::declare() {
    symbol::Table* table = symbol::Table::getInstance();

    //table->getSymbol(_name, _pos)->isUsed(true);

    if (_params)
        for (auto it : *_params)
            it->declare();
}

void FunCall::interpret() {
    interpretExpression();
}

ExpressionPtr FunCall::interpretExpression() {
    symbol::Table* table = symbol::Table::getInstance();
    symbol::FunSymbol* s = table->getFunSymbol(_name, _pos);
    if (s != NULL) {
        if (_params != NULL)
            for (auto& it : *_params)
                it = it->interpretExpression();
        return s->getPtr()->execute(_params);
    }
    else {
        // TODO exception
        cout << "Unknown function ! " << endl;
    }
    return NullExpression();
}

void FunCall::print(ostream& out, int offset) const {
    shift(out, offset);
    out << _name << " (";
    if (_params != NULL) {
        for (int i = 0; i < _params->size(); i++) {
            (*_params)[i]->print(out);
            if (i < _params->size() - 1)
                out << ", ";
        }
    }
    out << ")";
}

#include "Table.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Table* Table::instance = NULL;

Table::Table() {
    global_scope = new Scope();
    current_scope = nullptr;
}

Table::~Table() {}

Table* Table::getInstance() {
    if (instance == NULL)
        instance = new Table;
    return instance;
}

void Table::enterBlock() {
    if (current_scope) {
        current_scope = current_scope->newScope();
    }
    else {
        current_scope = global_scope;
    }
}

void Table::enterFunBlock(ast::FunctionPtr fun) {
    current_scope = current_scope->newFunScope();
    funcalls_stack.push(fun);
}

void Table::exitBlock() {
    if (current_scope) {
        // if the current scope and the main scope are the same, that means the end of the program, we delete the global scope
        if (current_scope == global_scope) {
            current_scope = nullptr;
        }
        else {
            // the current scope becomes the last current scope's parent
            Scope* tmp = current_scope->getParent();
            delete current_scope;
            current_scope = tmp;
        }
    }
    else {
        cout << "[Error] Cannot exit block." << endl;
        exit(-1);
    }
}

void Table::exitFunBlock() {
    Scope* tmp = current_scope->getParent();
    delete current_scope;
    current_scope = tmp;
    funcalls_stack.pop();
}

void Table::addSymbol(Symbol* s, Position* pos) {
    if (current_scope->getSymbol(s->getName(), pos) != nullptr)
        throw MultipleDefException(Global::getInstance()->file_name, pos, s->getName());
    current_scope->addSymbol(s, pos);
}

void Table::addFunSymbol(FunSymbol* s, Position* pos) {
    if (getFunSymbol(s->getName(), pos) != nullptr)
        throw MultipleDefException(Global::getInstance()->file_name, pos, s->getName());
    global_scope->addFunSymbol(s, pos);
}

Symbol* Table::getSymbol(string name, Position* pos) const {
    return current_scope->getSymbol(name, pos);
}

Symbol* Table::getGlobalSymbol(string name, Position* pos) const {
    return global_scope->getSymbol(name, pos);
}

FunSymbol* Table::getFunSymbol(string name, Position* pos) const {
    return global_scope->getFunSymbol(name, pos);
}

ast::FunctionPtr Table::getCurrentFunction() const {
    return funcalls_stack.top();
}

Scope* Table::getCurrentScope() const
{
    return current_scope;
}

string Table::toString() const {
    return current_scope->toString();
}

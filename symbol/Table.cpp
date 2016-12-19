#include "Table.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Table * Table::instance = NULL;

Table::Table() { current_scope = &main_scope; }
Table::~Table() {}

Table * Table::getInstance() {
    if (instance == NULL)
	instance = new Table;
    return instance;
}

void Table::enterBlock() {
    current_scope = current_scope->newScope();
}

void Table::exitBlock() {
    Scope * tmp = current_scope->getParent();
    if (tmp) {
	current_scope = tmp;
	current_scope->exitBlock ();
    } else {
	cout << "[Error] Cannot exit block." << endl;
	exit(-1);
    }
}

void Table::addSymbol(Symbol * s, ast::Position * pos) {
    current_scope->addSymbol(s, pos);
}

Symbol * Table::getSymbol(string name, ast::Position * pos) {
    return current_scope->getSymbol(name, pos);
}

string Table::toString() const {
    return current_scope->toString();
}

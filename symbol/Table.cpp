#include "Table.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Table * Table::instance = NULL;

Table::Table() {
    current_scope = NULL;
    global_scope = new Scope ();
}

Table::~Table() {}

Table * Table::getInstance() {
    if (instance == NULL)
	instance = new Table;
    return instance;
}

void Table::enterBlock() {
    if (current_scope) {
	current_scope = current_scope->newScope();
    } else {
	current_scope = global_scope;
    }
}

void Table::exitBlock() {
    if (current_scope) {
	// if the current scope and the main scope are the same, that means the end of the program, we delete the global scope
	if (current_scope == global_scope) {
	    delete global_scope;
	    global_scope = current_scope = NULL;
	} else {
	    // the current scope becomes the last current scope's parent
	    Scope * tmp = current_scope->getParent();
	    delete current_scope;
	    current_scope = tmp;
	}
    } else {
	cout << "[Error] Cannot exit block." << endl;
	exit(-1);
    }
}

void Table::addSymbol (Symbol * s, Position * pos) {
    if (current_scope->getSymbol (s->getName (), pos) != NULL)
	throw MultipleDefException(Global::getInstance()->file_name, pos, s->getName ());
    current_scope->addSymbol(s, pos);
}

Symbol * Table::getSymbol(string name, Position * pos) {
    Symbol * res = current_scope->getSymbol(name, pos);
    if (res == NULL)
	throw SymbolNotFoundException (Global::getInstance ()->file_name, pos, name);
    return res;
}

string Table::toString() const {
    return current_scope->toString ();
}

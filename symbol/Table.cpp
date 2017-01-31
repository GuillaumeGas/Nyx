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
	// if the current scope and the main scope are the same, that means the end of the program, we delete all the objects
	if (current_scope == global_scope) {
	    cout << "ici" << endl;
	    GarbageCollector::getInstance ()->free ();
	    GarbageCollector::getInstance ()->freeAll ();
	    delete global_scope;
	    global_scope = current_scope = NULL;
	} else {
	    cout << "et pas là" << endl;
	    // the current scope becomes the last current scope's parent
	    Scope * tmp = current_scope->getParent();
	    delete current_scope;
	    current_scope = tmp;
	    // we quit a bloc, so we delete all the objects that are no longer referenced
	    GarbageCollector::getInstance ()->free ();
	}
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

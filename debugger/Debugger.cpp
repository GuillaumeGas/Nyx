#include <iostream>

#include "Debugger.hpp"
#include "../symbol/Table.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;
using namespace debug;

Debugger* Debugger::instance = nullptr;

Debugger* Debugger::getInstance() {
    if (instance == nullptr)
	instance = new Debugger();
    return instance;
}

Debugger::Debugger() {}

Debugger::~Debugger() {}

void Debugger::debugBreak() {
    cout << "[nyx] Breakpoint hit !" << endl;

    string command;

    do {
	cout << " > ";
	cin >> command;

	if (command == "c") {
	    cout << "continue" << endl;
	}
	else if (command == "v") {
	    Table* table = Table::getInstance();
	    table->dumpVariablesOfCurrentScope();
	}
    } while (command != "c");
}


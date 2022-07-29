#include "Table.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Table* Table::instance = NULL;

Table::Table() {
	global_scope = new Scope();
	current_scope = global_scope;
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
		current_scope->checkForUnusedSymbols();

		// if the current scope and the main scope are the same, that means the end of the program, we delete the global scope
		if (current_scope == global_scope) {
			delete global_scope;
			global_scope = current_scope = NULL;
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
	current_scope->checkForUnusedSymbols();

	Scope* tmp = current_scope->getParent();
	delete current_scope;
	current_scope = tmp;
	funcalls_stack.pop();
}

void Table::addSymbol(Symbol* s, Position* pos) {
	if (current_scope->getSymbol(s->getName(), pos) != NULL)
		throw MultipleDefException(Global::getInstance()->file_name, pos, s->getName());
	current_scope->addSymbol(s, pos);
}

void Table::addFunSymbol(FunSymbol* s, Position* pos) {
	if (getFunSymbol(s->getName(), pos) != NULL)
		throw MultipleDefException(Global::getInstance()->file_name, pos, s->getName());
	global_scope->addFunSymbol(s, pos);
}

Symbol* Table::getSymbol(string name, Position* pos) {
	return current_scope->getSymbol(name, pos);
}

Symbol* Table::getGlobalSymbol(string name, Position* pos) {
	return global_scope->getSymbol(name, pos);
}

FunSymbol* Table::getFunSymbol(string name, Position* pos) {
	return global_scope->getFunSymbol(name, pos);
}

ast::FunctionPtr Table::getCurrentFunction() {
	return funcalls_stack.top();
}

string Table::toString() const {
	return current_scope->toString();
}

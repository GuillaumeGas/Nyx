#include "Bloc.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bloc::Bloc(vector<Ast*> * content) {
    pos = new DefaultPosition ();
    this->content = content;
    this->_is_global = false;
}

Bloc::Bloc (vector<Ast*> * content, bool is_global) {
    pos = new DefaultPosition ();
    this->content = content;
    this->_is_global = is_global;
}

Bloc::~Bloc() {
    for(Ast* a : *content) {
	if (a) {
	    delete a;
	}
    }
    delete content;
}

void Bloc::interpret() {
    symbol::Table * table = symbol::Table::getInstance ();
    if (_is_global)
	table->enterBlock ();

    for (Ast * a : *content)
	a->registerFunctions ();

    if (_is_global) {
	symbol::FunSymbol * main_symbol = table->getFunSymbol (MAIN_FUN_NAME, pos);
	if (main_symbol == NULL) {
	    cout << "[!] Main function not found !" << endl;
	    throw -1;
	}
	main_symbol->getPtr ()->execute (NULL);
    } else {
	for (Ast * a : *content)
	    a->interpret ();
    }

    if (_is_global)
	table->exitBlock ();
}

void Bloc::print (ostream & out, int offset) const {
    for(Ast* a : *content) {
	a->print (out, offset);
	out << endl;
    }
}

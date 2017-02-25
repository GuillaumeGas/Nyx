#include "Bloc.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bloc::Bloc(vector<Ast*> * content) {
    pos = new Position(0, 0);
    this->content = content;
    this->_is_global = false;
}

Bloc::Bloc (vector<Ast*> * content, bool is_global) {
    pos = new Position (0, 0);
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

void Bloc::secondPass () {
    symbol::Table * table = symbol::Table::getInstance ();
    if (_is_global)
	table->enterBlock ();

    for (Ast * a : *content)
	a->firstPass ();

    for (Ast * a : *content)
	a->secondPass ();

    if (_is_global)
	table->exitBlock ();
}

void Bloc::print (ostream & out, int offset) const {
    for(Ast* a : *content) {
	a->print (out, offset);
	out << endl;
    }
}

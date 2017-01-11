#include "Bloc.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bloc::Bloc(vector<Ast*> * content) {
    pos = new Position(0, 0);
    this->content = content;
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
    for (Ast * a : *content) {
	a->interpret();
    }
}

void Bloc::print (ostream & out, int offset) const {
    for(Ast* a : *content) {
	a->print (out, offset);
	out << endl;
    }
}

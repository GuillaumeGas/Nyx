#include "IfElse.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

IfElse::IfElse (Expression * cond, Bloc * bloc_if, Position * pos) {
    this->cond = cond;
    this->bloc_if = bloc_if;
    this->bloc_else = NULL;
    this->pos = pos;
}

IfElse::IfElse (Expression * cond, Bloc * bloc_if, Bloc * bloc_else, Position * pos) {
    this->cond = cond;
    this->bloc_if = bloc_if;
    this->bloc_else = bloc_else;
    this->pos = pos;
}

void IfElse::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "if ";
    cond->print (out);
    out << " {" << endl;
    bloc_if->print (out, offset+INDENT);
    if (bloc_else != NULL) {
	shift (out, offset);
	out << "} else {" << endl;
	bloc_else->print (out, offset+INDENT);
    }
    shift (out, offset);
    out << "}" << endl;;
}

void IfElse::interpret () {
    /*
      interpret la cond, si c'est true on interpret bloc_id, sinon, si bloc_else != NULL, l'interpreter
     */
}

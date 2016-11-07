#include "IfElse.hpp"

using namespace std;
using namespace bob;
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

string IfElse::to_string() const {
    string res = "IF " + cond->to_string() + " {\n" + bloc_if->to_string();
    if (bloc_else != NULL) {
	res += "} ELSE {\n" + bloc_else->to_string();
    }
    res += "}\n";
    return res;
}

void IfElse::interpret () {
    /*
      interpret la cond, si c'est true on interpret bloc_id, sinon, si bloc_else != NULL, l'interpreter
     */
}

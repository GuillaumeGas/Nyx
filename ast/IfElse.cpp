#include "IfElse.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

IfElse::IfElse (ExpressionPtr cond, BlocPtr bloc_if, Position * pos) {
    this->cond = cond;
    this->bloc_if = bloc_if;
    this->bloc_else = NULL;
    this->pos = pos;
}

IfElse::IfElse (ExpressionPtr cond, BlocPtr bloc_if, BlocPtr bloc_else, Position * pos) {
    this->cond = cond;
    this->bloc_if = bloc_if;
    this->bloc_else = bloc_else;
    this->pos = pos;
}

IfElse::~IfElse () {
}

void IfElse::interpret () {
    cond = cond->interpretExpression ();

    symbol::Table * table = symbol::Table::getInstance ();

    TYPE cond_type = cond->getType ()->value;

    if (cond_type != TYPE::BOOL)
    	throw SemanticErrorException ("Boolean expression expected !", cond->pos);

    if (cond->getBool () && bloc_if) {
    	table->enterBlock ();
    	bloc_if->interpret ();
    	table->exitBlock ();
    } else if (bloc_else) {
    	table->enterBlock ();
    	bloc_else->interpret ();
    	table->exitBlock ();
    }
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

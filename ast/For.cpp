#include "For.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

For::For (string * ident, VarId * var_loop, Expression * expr, Bloc * bloc, Position * pos) {
    this->ident = ident;
    this->var_loop = var_loop;
    this->expr = expr;
    this->bloc = bloc;
    this->pos = pos;
}


For::~For () {
    if (ident)
	delete ident;
    if (var_loop)
	delete var_loop;
    if (expr)
	delete expr;
    if (bloc)
	delete bloc;
}

void For::interpret() {
    TYPE expr_type = expr->getType ()->value;
    if (expr_type != TYPE::RANGE && expr_type != TYPE::ARRAY)
	throw SemanticErrorException ("The expression in a for loop should be an array or a range type ! Found : " + expr->getType ()->toString(), pos);

    symbol::Table * table = symbol::Table::getInstance ();
    table->enterBlock ();

    if (expr_type == TYPE::RANGE) {
	Range * range = (Range*)expr->interpretExpression ();
	int start = range->start->getValue ()->Int;
	int end = range->end->getValue ()->Int;

	table->addSymbol (new symbol::Symbol (var_loop->name, start), var_loop->pos);
	symbol::Symbol * loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);

	if (start < end) {
	    for (; start <= end; start++) {
		bloc->interpret ();
		loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);
		start = loop_symbol->getValue ()->Int;
		loop_symbol->setValue (start + 1);
	    }
	} else {
	    for (; start >= end; start--) {
		bloc->interpret ();
		loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);
		start = loop_symbol->getValue ()->Int;
		loop_symbol->setValue (start - 1);
	    }
	}
    } else {
	Array * array = (Array*)expr->interpretExpression ();

	table->addSymbol (new symbol::Symbol (var_loop->name, 0), var_loop->pos);
	symbol::Symbol * loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);

	for (auto it : *(array->array)) {
	    loop_symbol->setType (it->getType ());
	    updateSymbolValue (loop_symbol, it);
	    bloc->interpret ();
	}
    }

    table->exitBlock ();
}

void For::updateSymbolValue (symbol::Symbol * symbol, Expression * e) {
    switch (e->getType ()->value) {
    case TYPE::INT:
	symbol->setValue (e->getValue ()->Int);
	break;
    case TYPE::CHAR:
	symbol->setValue (e->getValue ()->Char);
	break;
    case TYPE::FLOAT:
	symbol->setValue (e->getValue ()->Float);
	break;
    case TYPE::BOOL:
	symbol->setValue (e->getValue ()->Bool);
	break;
    case TYPE::STRING:
	symbol->setValue (e->getValue ()->Str);
	break;
    default:
	throw SemanticErrorException ("updateSymbolValue : Unknown type !", e->pos);
    }
}

void For::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "For";
    if (ident)
	out << ":" << *ident;
    out << " (";
    var_loop->print (out);
    out << " in ";
    expr->print (out);
    out << ") {" << endl;
    bloc->print (out, offset+INDENT);
    shift (out, offset);
    out << "}";
}

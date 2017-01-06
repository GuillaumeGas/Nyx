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
    TYPE expr_type = expr->getValue ()->getType ()->value;
    if (expr_type != TYPE::RANGE && expr_type != TYPE::ARRAY)
	throw SemanticErrorException ("The expression in a for loop should be an array or a range type ! Found : " + expr->getValue ()->getType ()->toString(), pos);

    symbol::Table * table = symbol::Table::getInstance ();
    table->enterBlock ();

    if (expr_type == TYPE::RANGE) {
	Range * range = (Range*)(expr->interpretExpression ().getPtr ());
	int start = range->start->getValue ()->getInt ();
	int end = range->end->getValue ()->getInt ();

	table->addSymbol (new symbol::Symbol (var_loop->name, start), var_loop->pos);
	symbol::Symbol * loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);

	if (start < end) {
	    for (; start <= end; start++) {
		bloc->interpret ();
		loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);
		start = loop_symbol->getValue ()->getInt ();
		loop_symbol->setValue (start + 1);
	    }
	} else {
	    for (; start >= end; start--) {
		bloc->interpret ();
		loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);
		start = loop_symbol->getValue ()->getInt ();
		loop_symbol->setValue (start - 1);
	    }
	}
    } else {
	Array * array = (Array*)(expr->interpretExpression ().getPtr ());

	table->addSymbol (new symbol::Symbol (var_loop->name, 0), var_loop->pos);
	symbol::Symbol * loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);

	for (auto it : *(array->array)) {
	    loop_symbol->setType (it->getValue ()->getType ());
	    updateSymbolValue (loop_symbol, it);
	    bloc->interpret ();
	}
    }

    table->exitBlock ();
}

void For::updateSymbolValue (symbol::Symbol * symbol, Expression * e) {
    switch (e->getValue ()->getType ()->value) {
    case TYPE::INT:
	symbol->setValue (e->getValue ()->getInt ());
	break;
    case TYPE::CHAR:
	symbol->setValue (e->getValue ()->getChar ());
	break;
    case TYPE::FLOAT:
	symbol->setValue (e->getValue ()->getFloat ());
	break;
    case TYPE::BOOL:
	symbol->setValue (e->getValue ()->getBool ());
	break;
    case TYPE::STRING:
	symbol->setValue (e->getValue ()->getPtr ());
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

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

void For::interpret () {
    AbstractObject * obj_expr = (AbstractObject*) expr;
    TYPE expr_type = obj_expr->getType ()->value;

    if (expr_type != TYPE::RANGE && expr_type != TYPE::ARRAY)
    	throw SemanticErrorException ("The expression in a for loop should be an array or a range type ! Found : " + obj_expr->getType ()->toString(), pos);

    symbol::Table * table = symbol::Table::getInstance ();
    table->enterBlock ();

    if (expr_type == TYPE::RANGE) {
    	Range * range = (Range*)(obj_expr->interpretExpression ());
	Int * range_start = (Int*) range->getRangeStart ();
	Int * range_end = (Int*) range->getRangeEnd ();
    	int start = range->getRangeStart ()->getInt ();
    	int end = range->getRangeEnd ()->getInt ();

    	symbol::ConstSymbol * loop_symbol = new symbol::ConstSymbol (var_loop->name, (AbstractObject*)range_start->clone ());
    	table->addSymbol (loop_symbol, var_loop->pos);

    	if (start < end) {
    	    for (; start <= end; start++) {
		table->enterBlock ();
		bloc->interpret ();
		loop_symbol->getValue ()->setInt (start + 1);
		table->exitBlock ();
    	    }
    	} else {
    	    for (; start >= end; start--) {
		table->enterBlock ();
    		bloc->interpret ();
		loop_symbol->getValue ()->setInt (start - 1);
		table->exitBlock ();
    	    }
    	}

	if (loop_symbol->getValue ()->getNbRef () <= 0)
	    delete loop_symbol->getValue ();
    } else {
    	Array * array = (Array*)(expr->interpretExpression ());

    	symbol::ConstSymbol * loop_symbol = new symbol::ConstSymbol (var_loop->name);
    	table->addSymbol (loop_symbol, var_loop->pos);

    	for (auto it : *(array->getArray ())) {
	    table->enterBlock ();
	    loop_symbol->setConst (false);
	    loop_symbol->setValue ((AbstractObject*)it);
	    loop_symbol->setConst (true);
    	    bloc->interpret ();
	    table->exitBlock ();
    	}
    }
    table->exitBlock ();
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

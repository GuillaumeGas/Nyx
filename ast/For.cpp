#include "For.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

For::For (string * ident, VarIdPtr var_loop, ExpressionPtr expr, BlocPtr bloc, Position * pos) {
    this->ident = ident;
    this->var_loop = var_loop;
    this->expr = expr;
    this->bloc = bloc;
    this->pos = pos;
}


For::~For () {
    if (ident)
	delete ident;
}

void For::interpret () {
    // expr->interpretExpression ();
    // TYPE expr_type = expr->getType ()->value;

    // if (expr_type != TYPE::RANGE && expr_type != TYPE::ARRAY)
    // 	throw SemanticErrorException ("The expression in a for loop should be an array or a range type ! Found : " + expr->getType ()->toString(), pos);

    // symbol::Table * table = symbol::Table::getInstance ();
    // table->enterBlock ();

    // if (expr_type == TYPE::RANGE) {
    // 	IntPtr range_begin = expr->getRangeBegin ();
    // 	IntPtr range_end = expr->getRangeEnd ();
    // 	int begin = range_begin->getInt ();
    // 	int end = range_end->getInt ();

    // 	symbol::ConstSymbol * loop_symbol = new symbol::ConstSymbol (var_loop->name, range_start->clone ());
    // 	table->addSymbol (loop_symbol, var_loop->pos);

    // 	if (start < end) {
    // 	    for (; start <= end; start++) {
    // 		table->enterBlock ();
    // 		bloc->interpret ();
    // 		loop_symbol->getValue ()->setInt (start + 1);
    // 		table->exitBlock ();
    // 	    }
    // 	} else {
    // 	    for (; start >= end; start--) {
    // 		table->enterBlock ();
    // 		bloc->interpret ();
    // 		loop_symbol->getValue ()->setInt (start - 1);
    // 		table->exitBlock ();
    // 	    }
    // 	}
    // } else {
    // 	symbol::ConstSymbol * loop_symbol = new symbol::ConstSymbol (var_loop->name);
    // 	table->addSymbol (loop_symbol, var_loop->pos);

    // 	for (auto it : *(expr->getArray ())) {
    // 	    table->enterBlock ();
    // 	    loop_symbol->setConst (false);
    // 	    loop_symbol->setValue (it);
    // 	    loop_symbol->setConst (true);
    // 	    bloc->interpret ();
    // 	    table->exitBlock ();
    // 	}
    // }
    // table->exitBlock ();
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

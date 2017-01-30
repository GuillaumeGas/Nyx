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

    	symbol::Symbol * loop_symbol = new symbol::Symbol (var_loop->name, (AbstractObject*)range_start->clone ());
    	table->addSymbol (loop_symbol, var_loop->pos);

    	if (start < end) {
    	    for (; start <= end; start++) {
    		bloc->interpret ();

		// We check if the var loop has been modified during the last block, and we update it
		AbstractObject * loop_value = loop_symbol->getValue ();
		if (loop_value->getType ()->value != TYPE::INT)
		    throw SemanticErrorException ("You can't change the loop var type !", pos);

		Int * updated_loop_value = new Int (loop_value->getInt () + 1, new Position (pos->line, pos->column));
		if (loop_value->getNbRef () <= 0)
		    delete loop_value;
    	    }
    	} else {
    	    // for (; start >= end; start--) {
    	    // 	bloc->interpret ();
    	    // 	loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);
    	    // 	start = loop_symbol->getValue ()->getInt ();
    	    // 	loop_symbol->setValue (start - 1);
    	    // }
    	}
    } else {
    	// Array * array = (Array*)(expr->interpretExpression ());

    	// table->addSymbol (new symbol::Symbol (var_loop->name, 0), var_loop->pos);
    	// symbol::Symbol * loop_symbol = table->getSymbol (var_loop->name, var_loop->pos);

    	// for (auto it : *(array->array)) {
    	//     loop_symbol->setType (it->getValue ()->getType ());
    	//     // updateSymbolValue (loop_symbol, it);
    	//     bloc->interpret ();
    	// }
    }

    table->exitBlock ();
}

void For::updateSymbolValue (symbol::Symbol * symbol, AbstractObject * e) {
    // switch (e->getType ()->value) {
    // case TYPE::INT:
    // 	symbol->setValue (e->getInt ());
    // 	break;
    // case TYPE::CHAR:
    // 	symbol->setValue (e->getChar ());
    // 	break;
    // case TYPE::FLOAT:
    // 	symbol->setValue (e->getFloat ());
    // 	break;
    // case TYPE::BOOL:
    // 	symbol->setValue (e->getBool ());
    // 	break;
    // case TYPE::STRING:
    // 	symbol->setValue (e->getPtr ());
    // 	break;
    // default:
    // 	throw SemanticErrorException ("updateSymbolValue : Unknown type !", e->pos);
    // }
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

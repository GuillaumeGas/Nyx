#include "For.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

For::For (string * ident, VarIdPtr varLoop, ExpressionPtr expr, BlocPtr bloc, Position * pos) : Instruction (pos) {
    _ident = ident;
    _varLoop = varLoop;
    _expr = expr;
    _bloc = bloc;
}


For::~For () {
    if (_ident)
	delete _ident;
}

void For::interpret () {
    _expr = _expr->interpretExpression ();
    TYPE exprType = _expr->getType ()->value;

    if (exprType != TYPE::RANGE && exprType != TYPE::ARRAY)
    	throw SemanticErrorException ("The expression in a for loop should be an array or a range type ! Found : " + _expr->getType ()->toString(), _pos);

    symbol::Table * table = symbol::Table::getInstance ();
    table->enterBlock ();

    if (exprType == TYPE::RANGE) {
    	IntPtr rangeBegin = _expr->getRangeBegin ();
    	IntPtr rangeEnd = _expr->getRangeEnd ();
    	int begin = rangeBegin->getInt ();
    	int end = rangeEnd->getInt ();

    	symbol::ConstSymbol * loopSymbol = new symbol::ConstSymbol (_varLoop->getName (), rangeBegin->clone ());
    	table->addSymbol (loopSymbol, _varLoop->getPos ());

    	if (begin < end) {
    	    for (; begin <= end; begin++) {
    		table->enterBlock ();
    		_bloc->interpret ();
    		loopSymbol->getValue ()->setInt (begin + 1);
    		table->exitBlock ();
    	    }
    	} else {
    	    for (; begin >= end; begin--) {
    		table->enterBlock ();
    		_bloc->interpret ();
    		loopSymbol->getValue ()->setInt (begin - 1);
    		table->exitBlock ();
    	    }
    	}
    } else {
    	symbol::ConstSymbol * loopSymbol = new symbol::ConstSymbol (_varLoop->getName ());
    	table->addSymbol (loopSymbol, _varLoop->getPos ());

    	for (auto it : *(_expr->getArray ())) {
    	    table->enterBlock ();
    	    loopSymbol->setConst (false);
    	    loopSymbol->setValue (it);
    	    loopSymbol->setConst (true);
    	    _bloc->interpret ();
    	    table->exitBlock ();
    	}
    }
    table->exitBlock ();
}

void For::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "For";
    if (_ident)
	out << ":" << *_ident;
    out << " (";
    _varLoop->print (out);
    out << " in ";
    _expr->print (out);
    out << ") {" << endl;
    _bloc->print (out, offset+INDENT);
    shift (out, offset);
    out << "}";
}

std::string * For::getIdent () const {
    return _ident;
}

void For::setIdent (std::string * ident) {
    if (_ident)
	delete _ident;
    _ident = ident;
}

VarIdPtr For::getVarLoop () const {
    return _varLoop;
}

void For::setVarLoop (VarIdPtr varLoop) {
    _varLoop = varLoop;
}

ExpressionPtr For::getExpr () const {
    return _expr;
}

void For::setExpr (ExpressionPtr expr) {
    _expr = expr;
}

BlocPtr For::getBloc () const {
    return _bloc;
}

void For::setBloc (BlocPtr bloc) {
    _bloc = bloc;
}

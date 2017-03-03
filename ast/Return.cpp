#include "Return.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Return::Return (ExpressionPtr expr, Position * pos) {
    this->expr = expr;
    this->pos = pos;
}

Return::~Return () {
}

void Return::interpret () {
    symbol::Table * table = symbol::Table::getInstance ();
    Function * function = table->getCurrentFunction ();
    function->setRet (expr->interpretExpression ());
}

void Return::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "Return";
    if (expr) {
	out << " ";
	expr->print (out);
    }
}

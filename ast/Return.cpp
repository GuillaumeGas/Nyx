#include "Return.hpp"
#include "../symbol/Table.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Return::Return(ExpressionPtr expr, Position* pos) : Instruction(pos) {
    _expr = expr;
}

void Return::declare() {
    _expr->declare();
}

void Return::interpret() {
    symbol::Table* table = symbol::Table::getInstance();
    FunctionPtr function = table->getCurrentFunction();
    function->setRet(_expr->interpretExpression());
}

void Return::print(ostream& out, int offset) const {
    shift(out, offset);
    out << "Return";
    if (_expr != NULL) {
        out << " ";
        _expr->print(out);
    }
}

ExpressionPtr Return::getExpr() const {
    return _expr;
}

void Return::setExpr(ExpressionPtr expr) {
    _expr = expr;
}

#include "UnOp.hpp"

#include "Expression.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

UnOp::UnOp(Operator* op, ExpressionPtr expr, Position* pos) : Expression(pos) {
    _op = op;
    _expr = expr;
}

UnOp::~UnOp() {
    if (_op)
        delete _op;
}

void UnOp::print(ostream& out, int offset) const {
    out << "UnOp(" << _op->toString() << ", ";
    _expr->print(out, offset);
    out << ")";
}

ExpressionPtr UnOp::interpretExpression() {
    _expr = _expr->interpretExpression();
    ExpressionPtr res;

    Position* new_pos = new Position(_pos->line, _pos->column);

    switch (_op->value) {
    case Op::MINUS:
        res = _expr->interpretUnaryMINUS();
        break;
    default:
        throw SemanticErrorException("Unknown unary operator !", _pos);
    }

    res->setPos(new_pos);
    return res;
}

#include "Assign.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::Binop * Assign::visit (Syntax * syntax, Token * token_ident, Token * token_op) {
    ast::Expression * e1 = new ast::VarId (token_ident->value->to_string(), new ast::Position (token_ident->line, token_ident->column));
    ast::Expression * e2 = Expression::visit (syntax);
    ast::Operator * op = new ast::Operator (token_op->value->to_string());
    return new ast::Binop (e1, e2, op, new ast::Position (token_op->line, token_op->column));
}

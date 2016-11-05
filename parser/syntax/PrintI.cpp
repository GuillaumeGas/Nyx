#include "PrintI.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::Ast * PrintI::visit(Syntax * syntax, Token * token) {
  ast::Expression * expr = Expression::visit(syntax);
  ast::Position * pos = new ast::Position(token->line, token->column);
  return new ast::PrintI(expr, pos);
}

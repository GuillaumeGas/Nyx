#include "PrintI.hpp"
using namespace std;
using namespace bob;
using namespace syntax;

Instruction * PrintI::visit(Syntax * syntax, Token * token) {
  ast::Expression * expr = Expression::analyze(syntax);
  ast::Position * pos = new ast::Position(token->line, token->column);
  return new ast::PrintI(expr, pos);
}

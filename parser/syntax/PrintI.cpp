#include "PrintI.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void PrintI::analyze(Syntax * syntax, Token * token) {
  ast::Expression * expr = Expression::analyze(syntax);
  ast::Position * pos = new ast::Position(token->line, token->column);
  syntax->add_elem(new ast::PrintI(expr, pos));

  Program::analyze(syntax);
}

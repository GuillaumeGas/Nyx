#include "Assign.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Assign::analyze(bob::Syntax * syntax, Token * token_name) {
  ast::Expression * expr = Expression::analyze(syntax);
  if (expr == NULL)
    throw MissingErrorException("expression", Position(token_name->line, token_name->column));
  ast::Position * assign_pos = new ast::Position(token_name->line, token_name->column);
  ast::VarAssign * var_assign = new ast::VarAssign(token_name->value->to_string(), expr, assign_pos);
  syntax->add_elem(var_assign);

  Program::analyze(syntax);
}

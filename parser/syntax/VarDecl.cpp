#include "VarDecl.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void VarDecl::analyze(Syntax * syntax, unsigned int index, Token * token_type, Token * token_name) {
  ast::Type * type = new ast::Type(token_type->value->to_string(), true);
  ast::Position * pos = new ast::Position(token_type->line, token_type->column);
  ast::VarDecl * var_decl = new ast::VarDecl(type, token_name->value->to_string(), pos);

  syntax->add_elem(var_decl);
}

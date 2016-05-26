#include "Type.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Type::analyze(bob::Syntax * syntax, unsigned int index) {
  Token * type = syntax->get_token(index);
  Token * t = syntax->get_token(index+1);

  if(t->type == TokenType::IDENT) {
    Token * next = syntax->get_token(index+2);
    if (next->type == TokenType::SEMICOLON) {
      syntax->add_elem(new ast::VarDecl(new ast::Type(type->value->to_string(), true), t->value->to_string(), new ast::Position(type->line, type->column)));
    } else if(next->type == TokenType::ASSIGN) {
      syntax->add_elem(new ast::VarDecl(new ast::Type(type->value->to_string(), true), t->value->to_string(), new ast::Position(type->line, type->column)));
      Assign::analyze(syntax, index+1);
    } else {
      throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
    }
  } else {
    throw SyntaxErrorException(t->value->to_string(), Position(t->line, t->column));
  }
}

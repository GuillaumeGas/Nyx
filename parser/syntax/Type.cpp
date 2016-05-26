#include "Type.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Type::analyze(bob::Syntax * syntax, unsigned int index) {
  Token * type  = syntax->get_token(index);
  Token * ident = syntax->get_token(index+1);

  if(ident->type == TokenType::IDENT) {
    Token * next = syntax->get_token(index+2);
    if (next->type == TokenType::SEMICOLON) {
      VarDecl::analyze(syntax, index, type, ident);
      Program::analyze(syntax, index+3);
    } else if(next->type == TokenType::ASSIGN) {
      VarDecl::analyze(syntax, index, type, ident);
      Assign::analyze(syntax, index+1);
    } else {
      throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
    }
  } else {
    throw SyntaxErrorException(ident->value->to_string(), Position(ident->line, ident->column));
  }
}

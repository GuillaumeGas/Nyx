#include "Ident.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Ident::analyze(bob::Syntax * syntax, Token * token_ident) {
  Token * next = syntax->pop();
  if (next->type == TokenType::ASSIGN) {
    Assign::analyze(syntax, token_ident);
  } else {
    if (next != NULL)
      throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
    throw SyntaxErrorException(token_ident->value->to_string(), Position(token_ident->line, token_ident->column));
  }
}

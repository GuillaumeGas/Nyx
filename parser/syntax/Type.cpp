#include "Type.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Type::analyze(Syntax * syntax, Token * type) {
  Token * next = syntax->pop(); //on récupère la suite
  if(next->type == TokenType::IDENT) {
    Token * ident = next;
    next = syntax->pop();
    if (next->type == TokenType::SEMICOLON) {
      VarDecl::analyze(syntax, type, ident);
      Program::analyze(syntax);
    } else if(next->type == TokenType::ASSIGN) {
      VarDecl::analyze(syntax, type, ident);
      Assign::analyze(syntax, ident);
    } else {
      throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
    }
  } else {
    throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
  }
}

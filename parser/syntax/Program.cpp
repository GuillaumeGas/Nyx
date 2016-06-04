#include "Program.hpp"
#include "../Syntax.hpp"

using namespace bob;
using namespace syntax;
using namespace std;

void Program::analyze(Syntax * syntax) {
  Token * t = syntax->pop();
  if(t) {
    switch (t->type) {
    case TokenType::TYPE:
      Type::analyze(syntax, t);
      break;
    case TokenType::IDENT:
      Ident::analyze(syntax, t);
      break;
    case TokenType::PRINT_I:
      PrintI::analyze(syntax, t);
      break;
    default:
      throw SyntaxErrorException(t->value->to_string(), Position(t->line, t->column));
    }
  }
}

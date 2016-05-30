#include "Expression.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::Expression * Expression::analyze(Syntax * syntax) {
  Token * current_token = syntax->pop();;
  Token * last_token = NULL;
  ast::Ast * expr = NULL;
  if (current_token != NULL) {
    do {
      string val = current_token->value->to_string();
      if (Token::is_value(val)) {
	expr = Expression::create_value(current_token);
      } else if (Token::is_binop(val)) {
	last_token = current_token;
	current_token = syntax->pop();
	val = current_token->value->to_string();
	if (current_token == NULL) {
	  throw MissingErrorException("expression", Position(last_token->line, last_token->column));
	} else if (!Token::is_value(val)) {
	  throw SyntaxErrorException(current_token->value->to_string(), Position(current_token->line, current_token->column));
	}
	
	ast::Position * pos = new ast::Position(last_token->line, last_token->column);
	ast::Expression * right_expr = Expression::create_value(current_token);
	ast::BinOperator op = Expression::create_operator(last_token);
	ast::Binop * binop = new ast::Binop((ast::Expression*)expr, right_expr, op, pos);

	expr = (ast::Ast*) binop;
      }
      last_token = current_token;
      current_token = syntax->pop();
    } while (current_token != NULL && current_token->type != TokenType::SEMICOLON);
    return (ast::Expression*)expr;
  }
  return NULL;
}

ast::Expression * Expression::create_value(Token * token) {
  ast::Position * pos = new ast::Position(token->line, token->column);
  TokenValue * token_value = token->value;
  switch (token->type) {
  case TokenType::INT:
    return new ast::ConstInt(((TokenIntValue*)token_value)->value, pos);
    break;
  case TokenType::CHAR:
    return new ast::ConstChar(((TokenCharValue*)token_value)->value, pos);
    break;
  case TokenType::STRING:
    return new ast::ConstString(((TokenStringValue*)token_value)->value, pos);
    break;
  case TokenType::BOOL:
    return new ast::ConstBool(((TokenBoolValue*)token_value)->value, pos);
    break;
  default:
    throw SyntaxErrorException(token->value->to_string(), Position(token->line, token->column));
  }
  return NULL;
}

ast::BinOperator Expression::create_operator(Token * token) {
  ast::Position * pos = new ast::Position(token->line, token->column);
  switch (token->type) {
  case TokenType::PLUS:
    return ast::BinOperator::PLUS;
    break;
  case TokenType::MINUS:
    return ast::BinOperator::MINUS;
    break;
  case TokenType::MUL:
    return ast::BinOperator::MUL;
    break;
  case TokenType::DIV:
    return ast::BinOperator::DIV;
    break;
  case TokenType::MOD:
    return ast::BinOperator::MOD;
    break;
  default:
    throw SyntaxErrorException(token->value->to_string(), Position(token->line, token->column));
  }
}

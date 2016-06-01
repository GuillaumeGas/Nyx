#include <queue>
#include <stack>

#include "Expression.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::Expression * Expression::analyze(Syntax * syntax) {
  
  /* Transformation de l'expression en notation polonaise inversée */
  queue<Token*> out;
  stack<Token*> op;

  Token * current_token = syntax->pop();
  Token * tmp = NULL;

  while (current_token != NULL && current_token->type != TokenType::SEMICOLON) {
    string val = current_token->value->to_string();

    if (Token::is_value(val)) {
      out.push(current_token);
    } else if (Token::is_par_l(val)) {
      out.push(current_token);
    } else if (Token::is_par_r(val)) {
      tmp = op.top();
      while (tmp->type != TokenType::PAR_L && op.size() > 0) {
	out.push(tmp);
	op.pop();
	tmp = op.top();
      }
      if (tmp->type != TokenType::PAR_L) {
	throw SyntaxErrorException(tmp->value->to_string(), Position(tmp->line, tmp->column));
      } else {
	op.pop();
      }
    } else if (Token::is_binop(val)) {
      if (op.size() == 0 || op.top()->type == TokenType::PAR_L) {
	op.push(current_token);
      } else {
	ast::Operator op1(current_token->value->to_string());
	ast::Operator op2(op.top()->value->to_string());
	if (op1.priority > op2.priority) {
	  op.push(current_token);
	} else {
	  out.push(op.top());
	  op.pop();
	  op.push(current_token);
	}
      } 
    } else {
      throw SyntaxErrorException(tmp->value->to_string(), Position(tmp->line, tmp-column));
    }
  }
  while (op.size() > 0) {
    out.push(op.top());
    op.pop();
  }

  /* On prend la sortie et créé l'ast relatif à l'expression */
  


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

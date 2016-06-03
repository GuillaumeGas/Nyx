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

  while (current_token->type != TokenType::SEMICOLON) {
    string val = current_token->value->to_string();

    if (Token::is_value(current_token) || Token::is_ident(current_token)) {
      out.push(current_token);
    } else if (Token::is_par_l(current_token)) {
      op.push(current_token);
    } else if (Token::is_par_r(current_token)) {
      tmp = op.top();
      while (!Token::is_par_l(tmp) && op.size() > 0) {
	out.push(tmp);
	op.pop();
	if (op.size() > 0)
	  tmp = op.top();
      }
      if (!Token::is_par_l(tmp)) {
	throw SyntaxErrorException(tmp->value->to_string(), Position(tmp->line, tmp->column));
      } else {
	op.pop();
      }
    } else if (Token::is_binop(current_token)) {
      if (op.size() == 0 || Token::is_par_l(op.top())) {
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
      throw SyntaxErrorException(current_token->value->to_string(), Position(current_token->line, current_token->column));
    }
    
    Token * last = current_token;
    current_token = syntax->pop();

    if (current_token == NULL)
      throw MissingErrorException(";", Position(last->line, last->column));
  }
  while (op.size() > 0) {
    out.push(op.top());
    op.pop();
  }

  /* On prendl la sortie et créé l'ast relatif à l'expression */
  stack<ast::Expression*> st;

  while (out.size() > 0) {
    Token * t = out.front();
    out.pop();

    if (Token::is_value(t)) {
      st.push(Expression::create_value(t));
    } else if (Token::is_ident(t)) {
      st.push(new ast::VarId(t->value->to_string(), new ast::Position(t->line, t->column)));
    } else {
      ast::Operator * op = new ast::Operator(t->value->to_string());
      ast::Expression * e2 = st.top();
      st.pop();
      ast::Expression * e1 = st.top();
      st.pop();
      st.push(new ast::Binop(e1, e2, op, new ast::Position(t->line, t->column)));
    }
  }

  if (st.size() != 1)
    throw MissingErrorException("operator", Position(st.top()->pos->line, st.top()->pos->column));
  
  return st.top();
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
    cout << "tok " << token->to_string() << endl;
    throw SyntaxErrorException(token->value->to_string(), Position(token->line, token->column));
  }
  return NULL;
}

#include "Assign.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Assign::analyze(bob::Syntax * syntax, unsigned int index) {
  Token * var_name = syntax->get_token(index);
  Token * value    = syntax->get_token(index+2);
  Token * next     = syntax->get_token(index+3);

  if(syntax->get_token(index+1)->type == TokenType::ASSIGN) {
    if(value == NULL)
      throw MissingErrorException("rvalue", Position(var_name->line, var_name->column));
    if(next == NULL)
      throw MissingErrorException(";", Position(var_name->line, var_name->column));
    if(next->type == TokenType::SEMICOLON) {
      if(value->type == TokenType::INT) {
	ast::Position * value_pos = new ast::Position(value->line, value->column); 
	ast::Position * assign_pos = new ast::Position(var_name->line, var_name->column);
	TokenIntValue * int_val = (TokenIntValue*) value->value;
	syntax->add_elem(new ast::VarAssign(var_name->value->to_string(), new ast::IntValue(int_val->value, value_pos), assign_pos));
      } else if(value->type == TokenType::STRING) {
	ast::Position * value_pos = new ast::Position(value->line, value->column); 
	ast::Position * assign_pos = new ast::Position(var_name->line, var_name->column);
	TokenStringValue * string_val = (TokenStringValue*) value->value;
	syntax->add_elem(new ast::VarAssign(var_name->value->to_string(), new ast::StringValue(string_val->value, value_pos), assign_pos));
      } else if(value->type == TokenType::CHAR) {
	ast::Position * value_pos = new ast::Position(value->line, value->column); 
	ast::Position * assign_pos = new ast::Position(var_name->line, var_name->column);
	TokenCharValue * char_val = (TokenCharValue*) value->value;
	syntax->add_elem(new ast::VarAssign(var_name->value->to_string(), new ast::CharValue(char_val->value, value_pos), assign_pos));
      } else {
	throw SyntaxErrorException(value->value->to_string(), Position(value->line, value->column));
      }
    }
  } else {
    throw MissingErrorException("=", Position(var_name->line, var_name->column));
  }
}

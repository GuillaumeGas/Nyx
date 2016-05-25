#include "Assign.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace syntax;

void Assign::analyze(Syntax * syntax, unsigned int index) {
  Token * var_name = syntax->get_token(index);
  Token * value    = syntax->get_token(index+2);
  Token * next     = syntax->get_token(index+3);

  if(syntax->get_token(index+1)->type == TokenType::ASSIGN) {
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
      } else {
	cout << "Syntax error line " << value->line << endl;
      }
    } else {
      cout << "Syntax error line " << var_name->line << endl;
    }
  } else {
    cout << "Syntax error line " << var_name->line << endl;
  }
}

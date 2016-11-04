#include "IfElse.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::IfElse IfElse::visit (Syntax * syntax, Token * token) {
    ast::Expression * expr_condition = Expression::analyze (syntax);
    ast::Position * pos = new ast::Position (token->line, token->column);

    Token * next = syntax->pop();
    if (next->type != ACCOL_L) {
	throw MissingErrorException ("{", Position (next->line, next->column));
    }

    queue<ast::BlocInstruction> * instructions_list = BlocInstruction::visit(syntax);

    next = syntax->front();
    if (next->type == TokenType::ELSE) {
	syntax->pop();
	if (next->type != ACCOL_L) {
	    throw MissingErrorException ("{", Position (next->line, next->column));
	}
	queue<ast::BlocInstruction> * instructions_list_else = BlocInstruction::visit(syntax);
	return new ast::IfElse (expr_condition, instructions_list, instructions_list_else, pos);
    } else {
	return new ast::IfElse (expr_condition, instructions_list, pos);
    }
}

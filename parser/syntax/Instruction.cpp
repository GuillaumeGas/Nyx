#include "Instruction.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::Ast * Instruction::visit (Syntax * syntax, Token * token) {
    if (token->type == TokenType::IDENT) {
	Token * next = syntax->pop();
	if (next->type == TokenType::ASSIGN) {
	    ast::Ast * res = Assign::visit (syntax, token, next);
	    next = syntax->pop();
	    if (next->type != TokenType::SEMICOLON)
		throw MissingErrorException (";", Position (next->line, next->column));
	// } else if (next->type == TokenType::PAR_L) { //TODO FunCall::visit

	} else {
	    if (next != NULL)
		throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
	    throw SyntaxErrorException(token->value->to_string(), Position(token->line, token->column));
	}
    }
}

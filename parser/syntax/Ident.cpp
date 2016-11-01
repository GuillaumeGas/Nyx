#include "Ident.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Ident::analyze(bob::Syntax * syntax, Token * token_ident) {
    Token * next = syntax->pop();
    if (next->type == TokenType::ASSIGN) {
	ast::Expression * e1 = new ast::VarId (token_ident->value->to_string(), new ast::Position (token_ident->line, token_ident->column));
	ast::Expression * e2 = Expression::analyze (syntax);
	ast::Operator * op = new ast::Operator (next->value->to_string());
	syntax->add_elem (new ast::Binop (e1, e2, op, new ast::Position (next->line, next->column)));
	Program::analyze(syntax);
    } else {
	if (next != NULL)
	    throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
	throw SyntaxErrorException(token_ident->value->to_string(), Position(token_ident->line, token_ident->column));
    }
}

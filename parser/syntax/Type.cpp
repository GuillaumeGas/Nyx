#include "Type.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

void Type::analyze(Syntax * syntax, Token * type) {
    Token * next = syntax->pop();
    if(next->type == TokenType::IDENT) {
	Token * ident = next;
	next = syntax->pop();
	VarDecl::analyze(syntax, type, ident);
	if (next->type == TokenType::ASSIGN) {
	    ast::Expression * e1 = new ast::VarId (ident->value->to_string(), new ast::Position (ident->line, ident->column));
	    ast::Expression * e2 = Expression::analyze (syntax);
	    ast::Operator * op = new ast::Operator (next->value->to_string());
	    syntax->add_elem (new ast::Binop (e1, e2, op, new ast::Position (next->line, next->column)));
	} else if (next->type != TokenType::SEMICOLON) {
	    throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
	}
	Program::analyze(syntax);
    } else {
	throw SyntaxErrorException(next->value->to_string(), Position(next->line, next->column));
    }
}

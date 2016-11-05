#include "Decl.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::Ast * Decl::visit (Syntax * syntax, Token * type) {
    Token * ident = syntax->pop();
    if (ident->type != TokenType::IDENT)
	throw SyntaxErrorException (ident->value->to_string(), Position (ident->line, ident->column));
    Token * next = syntax->front();
    if (next->type == TokenType::PAR_L) {
	return Decl::visitFunDecl (syntax, type, ident);
    } else {
	return Decl::visitVarDecl (syntax, type, ident);
    }
}

ast::Ast * Decl::visitVarDecl (Syntax * syntax, Token * type, Token * ident) {
    Token * next = syntax->front();

    ast::Type * ast_type = new ast::Type (type->value->to_string(), true);
    ast::Position * pos = new ast::Position (type->line, type->column);
    ast::VarDecl * var_decl = new ast::VarDecl (ast_type, ident->value->to_string(), pos);
    ast::Ast * res;
    if (next->type == TokenType::ASSIGN) {
	ast::Binop * assign = Assign::visit (syntax, ident, next);
	deque<ast::Ast*> * instructions_list = new deque<ast::Ast*> ();
	instructions_list->push_back (var_decl);
	instructions_list->push_back (assign);
	res = new ast::InstructionBloc (instructions_list, pos);
    } else {
	res = var_decl;
    }
    next = syntax->pop();
    if (next->type != TokenType::SEMICOLON)
	throw MissingErrorException (";", Position (next->line, next->column));
    return res;
}

ast::Ast * Decl::visitFunDecl(Syntax * syntax, Token * type, Token * ident) {
    //TODO
}

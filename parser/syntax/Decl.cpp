#include "Type.hpp"
#include "../Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

Ast * Decl::visit (Syntax * syntax, Token * type) {
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

Ast * Decl::visitVarDecl (Syntax * syntax, Token * type, Token * ident) {
    Token * next = syntax->front();

    ast::Type * ast_type = new ast::Type (type->value->to_string(), true);
    ast::Position * pos = new ast::Position (type->line, type->column);
    ast::VarDecl * var_decl = new ast::VarDecl (ast_type, ident->value->to_string(), pos);
    //ON DEVRAIT PTET APPELER LA METHODE VISIT DE LA CLASSE ASSIGN, on aura besoin de assign ailleurs (dans instructionBloc, on peut tomber sur un ident tout seul
    if (next->type == TokenType::ASSIGN) {
	syntax->pop();
	ast::Expression * e1 = new ast::VarId (ident->value->to_string(), new ast::Position (ident->line, ident->column));
	ast::Expression * e2 = Expression::visit (syntax);
	ast::Operator * op = new ast::Operator (next->value->to_string());
	ast::Binop * assign = new ast::Binop (e1, e2, op, new ast::Position (next->line, next->column))
	queue<Instruction> * instructions_list = new queue<Instruction> ();
	instructions_list.push_back (var_decl);
	instructions_list.push_back (assign);
	return new ast::InstructionBloc (instructions_list, pos);
    } else {
	return var_decl;
    }
}

Ast * Decl::visitFunDecl(Syntax * syntax, Token * type, Token * ident) {
    //TODO
}

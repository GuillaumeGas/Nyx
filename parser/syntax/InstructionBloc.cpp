#include "InstructionBloc.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::InstructionBloc * InstructionBloc::visit(Syntax * syntax) {
    queue<ast::InstructionBloc> * instructions_list = new queue<ast::InstructionBloc> ();

    Token * t = syntax->pop();
    ast::Position * pos = new Position (t->line, t->column);
    ast::Ast * inst;
    while (t != NULL && t->type != TokenType::ACCOL_R) {
	switch (t->type) {
	case TokenType::TYPE:
	    inst = Decl::visit(syntax, t);
	    break;
	case TokenType::IDENT:
	    inst = Ident::visit(syntax, t);
	    break;
	case TokenType::PRINT_I:
	    inst = PrintI::visit(syntax, t);
	    break;
	case TokenType::IF:
	    inst = IfElse::visit(syntax, t);
	    break;
	default:
	    throw SyntaxErrorException(t->value->to_string(), Position(t->line, t->column));
	}
    }
    return new ast::InstructionBloc (instructions_list, pos);
}

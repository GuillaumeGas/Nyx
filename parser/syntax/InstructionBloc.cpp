#include "InstructionBloc.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

ast::InstructionBloc * InstructionBloc::visit(Syntax * syntax) {
    deque<ast::Ast*> * instructions_list = new deque<ast::Ast*> ();

    Token * t = syntax->pop();
    ast::Position * pos = new ast::Position (t->line, t->column);
    ast::Ast * inst;
    while (t != NULL && t->type != TokenType::ACCOL_R) {
	switch (t->type) {
	case TokenType::TYPE:
	    inst = Decl::visit(syntax, t);
	    break;
	case TokenType::IDENT:
	    inst = Instruction::visit(syntax, t);
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
	instructions_list->push_back (inst);
    }
    return new ast::InstructionBloc (instructions_list, pos);
}

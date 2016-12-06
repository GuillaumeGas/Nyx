#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <assert.h>

#include "Token.hpp"
#include "TokenList.hpp"
#include "Lexer.hpp"
#include "../ast/Ast.hpp"
#include "../ast/Bloc.hpp"
#include "../ast/Expression.hpp"
#include "../ast/Position.hpp"
#include "../ast/Type.hpp"
#include "../ast/VarDecl.hpp"
#include "../ast/Operator.hpp"
#include "../ast/Binop.hpp"
#include "../ast/VarAssign.hpp"
#include "../ast/VarId.hpp"
#include "../ast/ConstInt.hpp"
#include "../ast/ConstChar.hpp"
#include "../ast/ConstBool.hpp"
#include "../ast/ConstString.hpp"
#include "../ast/ConstFloat.hpp"
#include "../ast/IfElse.hpp"
#include "../ast/FunDecl.hpp"
#include "../ast/PrintI.hpp"
#include "../ast/For.hpp"
#include "../ast/While.hpp"
#include "../ast/Syscall.hpp"
#include "../ast/FunCall.hpp"
#include "../ast/Return.hpp"
#include "../ast/Break.hpp"
#include "../ast/UnOp.hpp"

#include "../symbol/Table.hpp"

#include "exceptions/SyntaxException.hpp"

#define TODO(p)					\
    printf ("[!] Unimplement token : %s\n", p);	\
    exit (-1);

namespace nyx {
    class Syntax {
    public:
	Syntax(Lexer & lex);
	~Syntax();

	ast::Ast * getAst() const;

	TokenPtr pop() const;
	void rewind ();

	/* Visitor */
	ast::Bloc * visitBloc ();
	ast::Ast * visitInstruction (TokenPtr token);
	ast::Ast * visitFunDecl (TokenPtr token_type, TokenPtr token_ident);
	ast::Ast * visitFunCall (TokenPtr token_ident);
	std::vector <ast::VarDecl*> * visitParamsDecl ();
	ast::Bloc * visitVarDecl (TokenPtr token_type, TokenPtr token_ident);
	ast::Ast * visitVarAssign (TokenPtr token_ident, TokenPtr token_op);
	ast::Ast * visitIfElse (TokenPtr token_if);
	ast::Ast * visitPrintI (TokenPtr token);
	ast::Ast * visitFor (TokenPtr token);
	ast::Ast * visitWhile (TokenPtr token);
	ast::Ast * visitSyscall (TokenPtr token);
	std::vector<ast::Expression*> * visitParams ();
	ast::Ast * visitReturn (TokenPtr token);
	ast::Ast * visitBreak (TokenPtr token);

	ast::Expression * visitExpression ();
	ast::Expression * visitLow ();
	ast::Expression * visitLow (ast::Expression * left);
	ast::Expression * visitHigh ();
	ast::Expression * visitHigh (ast::Expression * left);
	ast::Expression * visitHHigh ();
	ast::Expression * visitHHigh (ast::Expression * left);
	ast::Expression * visitLeft ();
	ast::Expression * visitConst ();
	ast::Expression * visitIdent ();
	ast::Expression * visitUnaryOp ();
	ast::Expression * visitConstFloat ();
	ast::Expression * visitConstInt ();
	ast::Expression * visitConstString ();
	ast::Expression * visitConstChar ();
	ast::Expression * visitConstBool ();

	bool find (TokenType type, std::vector <TokenType> list);

    private:
	Lexer & lex;
	ast::Bloc * m_program;

	symbol::Table * m_table;
    };
};

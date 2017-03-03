#pragma once

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <stack>
#include <assert.h>

#include "Token.hpp"
#include "TokenList.hpp"
#include "Lexer.hpp"
#include "../ast/AstIncludes.hpp"

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

	ast::AstPtr getAst() const;

	TokenPtr pop() const;
	void rewind (int count = 1);

	/* Visitor */
	ast::AstPtr visitBloc (bool global = false);
	ast::AstPtr visitInstruction ();
	ast::AstPtr visitFunDecl (TokenPtr token_type, TokenPtr token_ident);
	ast::AstPtr visitFunCall (TokenPtr token_ident);
	ast::ExpressionPtr visitExprFunCall (TokenPtr token_ident);
	std::vector <ast::VarDeclPtr> * visitParamsDecl ();
	ast::AstPtr visitLet ();
	ast::AstPtr visitVarDecl (TokenPtr token_ident);
	ast::AstPtr visitVarAssign (TokenPtr token_ident, TokenPtr token_op);
	ast::AstPtr visitIfElse ();
	ast::AstPtr visitFor ();
	ast::AstPtr visitWhile ();
	ast::AstPtr visitSyscall (TokenPtr token_ident);
	ast::AstPtr visitExprSyscall (TokenPtr token_ident);
	std::vector<ast::ExpressionPtr> * visitParams ();
	ast::AstPtr visitReturn ();
	ast::AstPtr visitBreak ();
	ast::AstPtr visitImport ();
	ast::AstPtr visitClass ();


	ast::ExpressionPtr visitExpression ();
	ast::ExpressionPtr visitULow ();
	ast::ExpressionPtr visitULow (ast::ExpressionPtr left);
	ast::ExpressionPtr visitLow ();
	ast::ExpressionPtr visitLow (ast::ExpressionPtr left);
	ast::ExpressionPtr visitHigh ();
	ast::ExpressionPtr visitHigh (ast::ExpressionPtr left);
	ast::ExpressionPtr visitHHigh ();
	ast::ExpressionPtr visitHHigh (ast::ExpressionPtr left);
	ast::ExpressionPtr visitHHHigh ();
	ast::ExpressionPtr visitHHHigh (ast::ExpressionPtr left);
	ast::ExpressionPtr visitLeft ();
	ast::ExpressionPtr visitIndex ();
	ast::ExpressionPtr visitConst ();
	ast::ExpressionPtr visitIdent ();
	ast::ExpressionPtr visitIdent (TokenPtr token_ident);
	ast::ExpressionPtr visitUnaryOp ();
	ast::ExpressionPtr visitFloat ();
	ast::ExpressionPtr visitInt ();
	ast::ExpressionPtr visitString ();
	ast::ExpressionPtr visitChar ();
	ast::ExpressionPtr visitBool ();
	ast::ExpressionPtr visitArray ();
	ast::ExpressionPtr visitCast ();

	bool find (TokenType type, std::vector <TokenType> list);
	bool isIdent (std::string value);

    private:
	Lexer & m_lex;
	ast::AstPtr m_program;

	symbol::Table * m_table;
    };
};

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
	Syntax(Lexer * lex, ast::Program * program);

	ast::Program * getAst() const;

	TokenPtr pop() const;
	void rewind (int count = 1);

	/* Visitor */
	void visitProgram ();
	ast::DeclarationPtr visitFunDecl ();
	ast::DeclarationPtr visitImport ();
	ast::DeclarationPtr visitClass ();

	ast::BlocPtr visitBloc ();
	ast::InstructionPtr visitInstruction ();
	ast::InstructionPtr visitFunCall (TokenPtr token_ident);
	ast::ExpressionPtr visitExprFunCall (TokenPtr token_ident);
	std::vector <ast::ParamPtr> * visitParamsDecl ();
	ast::InstructionPtr visitLet ();
	ast::InstructionPtr visitVarDecl (TokenPtr token_ident);
	ast::InstructionPtr visitVarAssign (TokenPtr token_ident, TokenPtr token_op);
	ast::InstructionPtr visitIfElse ();
	ast::InstructionPtr visitFor ();
	ast::InstructionPtr visitWhile ();
	ast::InstructionPtr visitSyscall (TokenPtr token_ident);
	ast::ExpressionPtr visitExprSyscall (TokenPtr token_ident);
	std::vector<ast::ExpressionPtr> * visitParams ();
	ast::InstructionPtr visitReturn ();
	ast::InstructionPtr visitBreak ();

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
	Lexer * _lex;
	ast::Program * _program;

	symbol::Table * _table;
    };
};

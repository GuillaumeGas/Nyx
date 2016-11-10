#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <assert.h>

#include "Token.hpp"
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
#include "../ast/IfElse.hpp"
#include "../ast/FunDecl.hpp"
#include "../ast/PrintI.hpp"
#include "../ast/For.hpp"
#include "../ast/While.hpp"

#include "../symbol/Table.hpp"

#include "exceptions/SyntaxException.hpp"

#define TODO(p)						\
    printf ("[!] Unimplement token : %s\n", p);				\
    exit (-1);

namespace bob {
    class Syntax {
    public:
	Syntax(std::string& file_name, std::queue<Token*> * tokens);
	~Syntax();

	ast::Ast * get_ast() const;

	Token * pop() const;
	Token * front() const;
	void add_elem(ast::Ast * elem);
	bool is_empty () const;

	/* Visitor */
	ast::Bloc * visitBloc ();
	ast::Ast * visitInstruction (Token * token);
	ast::Ast * visitFunDecl (Token * token_type, Token * token_ident);
	ast::Ast * visitFunCall (Token * token_ident);
	std::vector <ast::VarDecl*> * visitParamsDecl ();
	ast::Bloc * visitVarDecl (Token * token_type, Token * token_ident);
	ast::Ast * visitVarAssign (Token * token_ident);
	ast::Ast * visitIfElse (Token * token_if);
	ast::Ast * visitPrintI (Token * token);
	ast::Ast * visitFor (Token * token);
	ast::Ast * visitWhile (Token * token);

	ast::Expression * visitExpression ();
	ast::Expression * create_value (Token * token);
	bool is_part_of_expr (Token * token) const;

    private:
	std::string m_file_name;

	std::queue<Token*> * m_tokens;
	ast::Bloc * m_program;

	symbol::Table * m_table;
    };
};

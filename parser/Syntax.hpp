#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>

#include "Token.hpp"
#include "../ast/Ast.hpp"
#include "../ast/Program.hpp"
#include "../ast/Expression.hpp"
#include "../ast/Position.hpp"
#include "../ast/Type.hpp"
#include "../ast/VarDecl.hpp"
#include "../ast/Operator.hpp"
#include "../ast/Binop.hpp"
#include "../ast/VarId.hpp"
#include "../ast/ConstInt.hpp"
#include "../ast/ConstChar.hpp"
#include "../ast/ConstBool.hpp"
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
	void visitBloc ();
	void visitInstruction (Token * token);
	void visitFunDecl (Token * token_type, Token * token_ident);
	void visitVarDecl (Token * token_type, Token * token_ident);
	void visitVarAssign (Token * token_ident, Token * token_op);
	void visitIfElse ();
	ast::Expression * visitExpression ();
	ast::Expression * create_value (Token * token);
	bool is_part_of_expr (Token * token) const;

    private:
	std::string m_file_name;

	std::queue<Token*> * m_tokens;
	ast::Program * m_program;

	symbol::Table * m_table;
    };
};

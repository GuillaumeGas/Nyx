#pragma once

#include <iostream>
#include <queue>
#include <fstream>

#include "../parser/Token.hpp"
#include "../parser/Lexer.hpp"
#include "../parser/Syntax.hpp"
#include "../parser/exceptions/LexerException.hpp"
#include "../parser/exceptions/SyntaxException.hpp"
#include "../ast/Ast.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/exceptions/SymbolException.hpp"

namespace nyx {
    class Compilo {
    public:
	Compilo(std::string file_name);
	~Compilo();

	void compile();
	void printAst() const;

    private:
	Lexer * m_lex;
	Syntax * m_syn;

	std::string m_file_name;
	std::queue<Token*> * m_tokens;
	ast::Ast * m_ast;
    };
};

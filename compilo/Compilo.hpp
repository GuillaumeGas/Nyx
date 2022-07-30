#pragma once

#include <iostream>
#include <queue>
#include <fstream>

#include "../parser/Token.hpp"
#include "../parser/Lexer.hpp"
#include "../parser/Syntax.hpp"
#include "../parser/exceptions/LexerException.hpp"
#include "../parser/exceptions/SyntaxException.hpp"

#include "../ast/Program.hpp"

#include "../symbol/Table.hpp"
#include "../symbol/StaticAnalysis.hpp"
#include "../symbol/exceptions/SymbolException.hpp"
#include "../global/Global.hpp"

namespace nyx {
    class Compilo {
    public:
        Compilo(std::string file_name);
        ~Compilo();

        void compile();
        void printAst() const;

    private:
        Lexer* _lex;
        Syntax* _syn;

        std::string _file_name;
        ast::Program* _program;
    };
};

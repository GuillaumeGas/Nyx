#pragma once

#include <iosfwd>

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

#define DllExport __declspec(dllexport)

namespace nyx {
    class DllExport Compilo {
    public:
        Compilo(std::string file_name, bool debug_mode = false);
        ~Compilo();

        int compile();
        void printAst() const;

        static Lexer* PassFileThroughLexer(std::string fileName);
        static ast::Program* CreateAst(Lexer* lexer);

    private:
        Lexer* _lex;
        Syntax* _syn;

        std::string _file_name;
        ast::Program* _program;
    };
};

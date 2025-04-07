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

#include "../NyxQt_global.h"

namespace nyx {
    class NYXQT_EXPORT Compilo {
    public:
        Compilo(std::string file_name, std::ostream & outstream = std::cout, bool debug_mode = false);
        ~Compilo();

        int compile();
        void printAst() const;

        static Lexer* PassFileThroughLexer(std::string fileName, std::ostream & outstream = std::cout);
        static ast::Program* CreateAst(Lexer* lexer, std::ostream & outstream = std::cout);

    private:
        Lexer* _lex;
        Syntax* _syn;

        std::string _file_name;
        ast::Program* _program;

        std::ostream & _outstream;
    };
};

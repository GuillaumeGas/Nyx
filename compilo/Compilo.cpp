#include "Compilo.hpp"

using namespace std;
using namespace nyx;

bool g_debugNyx = false;

#ifdef _DEBUG_NYX_
g_debugNyx = true;
#endif // _DEBUG_NYX_

Compilo::Compilo(string file_name, bool debug_mode) {
    _file_name = file_name;
    _lex = nullptr;
    _program = nullptr;
    g_debugNyx = debug_mode;
}

Compilo::~Compilo() {
    if (_lex)
        delete _lex;
    if (_syn)
        delete _syn;
    if (_program)
        delete _program;

    // we don't forget to free the global data...
    Global::getInstance()->release();
    // and the symbols table
    symbol::Table::getInstance()->release();
}

Lexer* Compilo::PassFileThroughLexer(string fileName)
{
    try {
        Lexer * lex = new Lexer(fileName);
        lex->setKeys({ "+", "++", "-", "--", "*", "/", "%", "%=", "<", "<=", ">", ">=", "!",
                "==", "!=", "(", ")", "=", "+=", "-=", "*=", "/=", "{", "}", "[", "]", ";", ",", ":",
                ".", "..", "$", "~", "\"", "\\", "'",
                " ", "/*", "*/", "//", "\n", "\r", "\t" });
        lex->setSkips({ " ", "\n", "\r", "\t" });
        lex->setComs({ make_pair("/*", "*/"), make_pair("//", "\n") });

        return lex;
    }
    catch (LexerException const& e) {
        cout << e.toString() << endl;
        exit(-1);
    }
}

ast::Program* Compilo::CreateAst(Lexer* lexer)
{
    try {
        Syntax syn(lexer);
        return syn.getAst();
    }
    catch (SyntaxException const& e) {
        cout << e.toString() << endl;
        exit(-1);
    }
}

int Compilo::compile()
{
    _lex = PassFileThroughLexer(_file_name);

    if (g_debugNyx)
        cout << "/------------------------- AST ------------------------\\" << endl << endl;

    _program = CreateAst(_lex);
    if (g_debugNyx)
    {
        printAst();
        cout << endl << endl;
    }

    if (g_debugNyx)
    {
        try {
            _program->staticAnalysis();
            symbol::StaticAnalysis::getInstance()->displayUnusedSymbols();
            cout << endl << endl;
        }
        catch (SyntaxException const& e) {
            cout << e.toString() << endl;
            exit(-1);
        }

        symbol::Table::getInstance()->release();
    }

    if (g_debugNyx)
        cout << "/---------------------- Execution ----------------------\\" << endl << endl;
    try {
        _program->execute();
        if (g_debugNyx)
            cout << endl;
    }
    catch (SymbolException const& e) {
        cout << e.toString() << endl;
        exit(-1);
    }
    catch (SemanticErrorException const& e) {
        cout << e.toString() << endl;
        exit(-1);
    }

    return _program->getMainResult();
}

void Compilo::printAst() const {
    _program->print();
}



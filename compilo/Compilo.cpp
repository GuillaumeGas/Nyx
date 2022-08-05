#include "Compilo.hpp"

using namespace std;
using namespace nyx;

Compilo::Compilo(string file_name) {
    _file_name = file_name;
    _lex = nullptr;
    _program = nullptr;
}

Compilo::~Compilo() {
    if (_lex)
        delete _lex;
    if (_syn)
        delete _syn;
    if (_program)
        delete _program;

    // we don't forget to free the global data...
    delete Global::getInstance();
    // and the symbols table
    delete symbol::Table::getInstance();
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

void Compilo::compile()
{
    _lex = PassFileThroughLexer(_file_name);

    cout << "/------------------------- AST ------------------------\\" << endl << endl;

    _program = CreateAst(_lex);
    printAst();
    cout << endl << endl;

    cout << "/------------------- Static Analysis -------------------\\" << endl << endl;
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

    cout << "/---------------------- Execution ----------------------\\" << endl << endl;
    try {
        _program->execute();
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
}

void Compilo::printAst() const {
    _program->print();
}



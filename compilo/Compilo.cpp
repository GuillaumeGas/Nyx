#include "Compilo.hpp"

using namespace std;
using namespace nyx;

Compilo::Compilo(string file_name) {
    _file_name = file_name;
    _lex = NULL;
    _syn = NULL;
    _program = new ast::Program;
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

void Compilo::compile() {
    try {
        _lex = new Lexer(_file_name);
        _lex->setKeys({ "+", "++", "-", "--", "*", "/", "%", "%=", "<", "<=", ">", ">=", "!",
                "==", "!=", "(", ")", "=", "+=", "-=", "*=", "/=", "{", "}", "[", "]", ";", ",", ":",
                ".", "..", "$", "~", "\"", "\\", "'",
                " ", "/*", "*/", "//", "\n", "\r", "\t" });
        _lex->setSkips({ " ", "\n", "\r", "\t" });
        _lex->setComs({ make_pair("/*", "*/"), make_pair("//", "\n") });
    }
    catch (LexerException const& e) {
        cout << e.toString() << endl;
        exit(-1);
    }

    cout << "/------------------------- AST ------------------------\\" << endl << endl;
    try {
        _syn = new Syntax(_lex, _program);
        _program = _syn->getAst();
        printAst();
        cout << endl << endl;
    }
    catch (SyntaxException const& e) {
        cout << e.toString() << endl;
        exit(-1);
    }

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



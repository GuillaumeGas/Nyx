
#include "Compilo.hpp"

using namespace std;
using namespace nyx;

Compilo::Compilo(string file_name) {
    m_file_name = file_name;
    m_lex = NULL;
    m_syn = NULL;
}

Compilo::~Compilo() {
    if (m_lex)
	delete m_lex;
    if (m_syn)
	delete m_syn;

    // we don't forget to free the global data...
    delete Global::getInstance ();
    // and the symbols table
    delete symbol::Table::getInstance ();
}

void Compilo::compile() {
    try {
	m_lex = new Lexer(m_file_name);
	m_lex->setKeys ({"+", "++", "-", "--", "*", "/", "%", "%=", "<", "<=", ">", ">=", "!",
		    "==", "!=", "(", ")", "=", "+=", "-=", "*=", "/=", "{", "}", "[", "]", ";", ",", ":",
		    ".", "..", "$", "~", "\"", "\\", "'",
		    " ", "/*", "*/", "//", "\n", "\r", "\t"});
	m_lex->setSkips ({" ", "\n", "\r", "\t"});
	m_lex->setComs ({make_pair ("/*", "*/"), make_pair ("//", "\n")});
    } catch(LexerException const& e) {
	cout << e.toString() << endl;
	exit(-1);
    }

    cout << "/------------------- AST -------------------\\" << endl << endl;
    try {
    	m_syn = new Syntax(*m_lex);
    	m_ast = m_syn->getAst();
    	printAst ();
    	cout << endl;
    } catch(SyntaxException const& e) {
    	cout << e.toString() << endl;
    	exit(-1);
    }

    cout << "/---------------- Execution -----------------\\" << endl << endl;
    try {
      m_ast->secondPass ();
      cout << endl;
    } catch(SymbolException const& e) {
      cout << e.toString () << endl;
      exit(-1);
    } catch(SemanticErrorException const& e) {
      cout << e.toString () << endl;
      exit(-1);
    }
}

void Compilo::printAst() const {
    m_ast->print (cout);
    cout.flush ();
}




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
}

void Compilo::compile() {
    try {
	m_lex = new Lexer(m_file_name);
	m_lex->setKeys ({"+", "++", "-", "--", "*", "/", "%", "%=", "<", "<=", ">", ">=",
		    "==", "!=", "(", ")", "=", "+=", "-=", "*=", "/=", "{", "}", "[", "]", ";", ",", ":",
		    ".", "..", "$", "\"", "\\", "'",
		    " ", "/*", "*/", "//", "\n", "\r", "\t"});
	m_lex->setSkips ({" ", "\n", "\r", "\t"});
	m_lex->setComs ({make_pair ("/*", "*/"), make_pair ("//", "\n")});
    } catch(LexerException const& e) {
	cout << e.toString() << endl;
	exit(-1);
    }

    try {
    	m_syn = new Syntax(*m_lex);
    	m_ast = m_syn->getAst();
    } catch(SyntaxException const& e) {
    	cout << e.toString() << endl;
    	exit(-1);
    }

    // cout << "Interpret..." << endl;
    // try {
    //   m_ast->interpret();
    //   cout << "End" << endl;
    // } catch(SymbolException const& e) {
    //   cout << e.to_string() << endl;
    //   exit(-1);
    // } catch(SemanticException const& e) {
    //   cout << e.to_string() << endl;
    //   exit(-1);
    // }

    // cout << symbol::Table::get_instance()->to_string() << endl;
}

void Compilo::printAst() const {
    m_ast->print (cout);
    cout.flush ();
}



#include "Compilo.hpp"

using namespace std;
using namespace bob;

Compilo::Compilo(string file_name) {
  m_file_name = file_name;
}

Compilo::~Compilo() {
  for(Token* t : m_tokens) {
    if (t) {
      delete t;
    }
  }

  if (m_lex)
    delete m_lex;
  if (m_syn)
    delete m_syn;
}

void Compilo::compile() {
  try {
    m_lex = new Lexer(m_file_name);
    m_tokens = m_lex->get_tokens();
  } catch(LexerException const& e) {
    cout << e.to_string() << endl;
    exit(-1);
  } 
  try {
    m_syn = new Syntax(m_file_name, m_tokens);
    m_ast = m_syn->get_ast();
  } catch(SyntaxException const& e) {
    cout << e.to_string() << endl;
    exit(-1);
  }
}

void Compilo::print_tokens() const {
  for(Token* t : m_tokens) {
    cout << t->to_string() << endl;
  }
}

void Compilo::print_ast() const {
  cout << m_ast->to_string() << endl;
}



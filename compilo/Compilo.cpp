#include "Compilo.hpp"

using namespace std;
using namespace bob;

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

  cout << "Interpret..." << endl;
  m_ast->interpret();
  cout << "End" << endl;

  cout << symbol::Table::get_instance()->to_string() << endl;
}

void Compilo::print_tokens() const {
  // Token * t = NULL;
  // while (m_tokens->size() > 0) {
  //   t = m_tokens->front();
  //   t->to_string();
  //   m_tokens->pop();
  //   delete t;
  // }
}

void Compilo::print_ast() const {
  cout << m_ast->to_string() << endl;
}



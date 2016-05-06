#include "Compilo.hpp"

using namespace std;

Compilo::Compilo() {}
Compilo::~Compilo() {
  for(Token* t : m_tokens) {
    if (t) {
      delete t;
    }
  }
}

void Compilo::compile(string file_name) {
  Lexer lex(file_name);
  m_tokens = lex.get_tokens();
  
  Syntaxe syn(file_name, m_tokens);
  m_ast = syn.get_ast();
}

void Compilo::print_tokens() const {
  for(Token* t : m_tokens) {
    cout << t->to_string() << endl;
  }
}

void Compilo::print_ast() const {
  cout << m_ast->to_string() << endl;
}



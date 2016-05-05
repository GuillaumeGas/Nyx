#include "Compilo.hpp"

using namespace std;

Compilo::Compilo() {}
Compilo::~Compilo() {
  for(Token* t : m_tokens) {
    if (t)
      delete t;
  }
}

void Compilo::compile(string file_name) {
  Lexer lex(file_name);
  lex.analyze();
  m_tokens = lex.get_tokens();
  
  // Syntaxe syn(file_name);
  // syn.analyse();
}

void Compilo::print_tokens() const {
  for(Token* t : m_tokens) {
    cout << t->to_string() << endl;
  }
}



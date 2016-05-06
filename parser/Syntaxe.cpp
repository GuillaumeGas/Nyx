#include "Syntaxe.hpp"

using namespace std;
using namespace ast;

Syntaxe::Syntaxe(string& file_name, vector<Token*>& tokens) : m_file_name(file_name), m_tokens(tokens) {
  m_program = new Program();
  m_index = 0;
  while(m_index < m_tokens.size()) {
    analyze_current_token();
  }
}

void Syntaxe::analyze_current_token() {
  Token * t = m_tokens[m_index];
  if(t->type == TokenType::TYPE) {
    if(m_tokens[m_index+1]->type == TokenType::IDENT && m_tokens[m_index+2]->type == TokenType::SEMICOLON) {
      m_program->content.push_back(new VarDecl(new Type(t->type_to_string(), true), t->value->to_string()));
    }
  }
  m_index++;
}

TokenType Syntaxe::getTokenType(unsigned int index) {
  //TODO, on check si on sort pas du tableau, etc...l
}

Ast * Syntaxe::get_ast() const {
  return m_program;
}

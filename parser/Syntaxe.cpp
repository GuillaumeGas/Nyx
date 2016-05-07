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

Syntaxe::~Syntaxe() {
  if(m_program) {
    delete m_program;
  }
}

void Syntaxe::analyze_current_token() {
  Token * t = getToken(m_index);
  if(t->type == TokenType::TYPE) {
    if(getToken(m_index+1)->type == TokenType::IDENT && getToken(m_index+2)->type == TokenType::SEMICOLON) {
      Token * t_ident = getToken(m_index+1);
      m_program->content.push_back(new VarDecl(new Type(t->value->to_string(), true), t_ident->value->to_string(), new Position(t->line, t->column)));
    }
  }
  m_index++;
}

Token * Syntaxe::getToken(unsigned int index) {
  if(index >= 0 && index < m_tokens.size())
    return m_tokens[index];
}

Ast * Syntaxe::get_ast() const {
  return m_program;
}

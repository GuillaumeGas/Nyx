#include "Syntax.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Syntax::Syntax(string& file_name, queue<Token*> * tokens) : m_file_name(file_name), m_tokens(tokens) {
  m_program = new Program();
  syntax::Program::analyze(this);
}

Syntax::~Syntax() {}

Token * Syntax::pop() {
  Token * t = m_tokens->front();
  m_tokens->pop();
  return t;
}

void Syntax::add_elem(Ast * elem) {
  if (elem != NULL)
    m_program->content.push_back(elem);
}

Ast * Syntax::get_ast() const {
  return m_program;
}

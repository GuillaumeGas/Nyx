#include "Syntax.hpp"

using namespace std;
using namespace ast;
using namespace bob;

Syntax::Syntax(string& file_name, vector<Token*>& tokens) : m_file_name(file_name), m_tokens(tokens) {
  m_program = new Program();
  // try {
    bob::syntax::Program program;
    program.analyze(this, 0);
  // } catch (SyntaxException const& e) {
  //   cout << e.to_string() << endl;
  // }
}

Syntax::~Syntax() {
  if(m_program) {
    delete m_program;
  }
}

void Syntax::add_elem(Ast * elem) {
  if (elem != NULL)
    m_program->content.push_back(elem);
}

Token * Syntax::get_token(unsigned int index) {
  if(index >= 0 && index < m_tokens.size()) {
    return m_tokens[index];
  } else {
    return NULL;
  }
}

Ast * Syntax::get_ast() const {
  return m_program;
}

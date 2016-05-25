#include "Syntax.hpp"

using namespace std;
using namespace ast;

Syntax::Syntax(string& file_name, vector<Token*>& tokens) : m_file_name(file_name), m_tokens(tokens) {
  m_program = new Program();

  syntax::Program program;
  program.analyze(this, 0);
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

// void Syntax::analyze_current_token() {
//   Token * t = getToken(m_index);
//   switch(t->type) {
//   case TokenType::TYPE:
//     start_by_type(t);
//     break;
//   default:
//     error(t);
//   }
//   m_index++;
// }

// void start_by_type(Token * t) {
//   if(getToken(m_index+1)->type == TokenType::IDENT) {
//     if(getToken(m_index+2)->type == TokenType::SEMICOLON) {
//       Token * t_ident = getToken(m_index+1);
//       m_program->content.push_back(new VarDecl(new Type(t->value->to_string(), true), t_ident->value->to_string(), new Position(t->line, t->column)));
//     } else if(getToken(m_index+2)->type == TokenType::ASSIGN) {
//       if(getToken(m_index+3)->type == TokenType::INT || getToken(m_index+3)->type == TokenType::STRING
//       cout << "Syntax error line " << t->line << endl;
//     }
//   } else {
//     error(t);
//   }
// }

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

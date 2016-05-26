#include "Lexer.hpp"

using namespace std;
using namespace bob;

Lexer::Lexer(string file_name) : m_file_name(file_name) {
  m_line = 1;

  ifstream file(m_file_name.c_str(), std::ios::in);
  if(file.is_open()) {
    while (getline(file, m_current_line)) {
      m_current_index = 0;
      next_line();
      m_line++;
    }
  } else {
    throw FileNotFoundException(file_name);
  }
}

void Lexer::next_line() {
  while (m_current_index < m_current_line.size()) {
    m_tmp_col = -1;
    next_word();
    register_token();
  }
}

void Lexer::next_word() {
  m_token = "";
  char c = m_current_line[m_current_index];
  int i = 0;
  while ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '\'' || c == '"' || c == '_') {
    if(m_tmp_col < 0) {
      m_tmp_col = m_current_index+1;
    }
    m_token += c;
    m_current_index++;
    c = m_current_line[m_current_index];
    i++;
  }
  if(i == 0) {
    if(c != ' ') {
      m_tmp_col = m_current_index+1;
      m_token = c;
      if(c == '>' || c == '<' || c == '=' || c == '!') {
	char next = m_current_line[m_current_index+1];
	if(next == '>' || next == '<' || next == '=') {
	  m_token += next;
	  m_current_index++;
	}
      }
    }
    m_current_index++;
  }
}

void Lexer::register_token() {
  m_column = m_tmp_col;
  if(m_token.size() > 0) {
    Token * t = Token::create(m_token, m_line, m_column);
    if(t) {
      m_tokens.push_back(t);
      m_column = -1;
    } else {
      throw TokenErrorException(m_file_name, m_token, m_line, m_column);
    }
  }
}

vector<Token*> Lexer::get_tokens() const {
  return m_tokens;
}

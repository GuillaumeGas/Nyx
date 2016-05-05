#include "Lexer.hpp"

using namespace std;

Lexer::Lexer(string file_name) : m_file_name(file_name) {}

void Lexer::analyze() {
  m_line = 0;

  ifstream file(m_file_name.c_str(), std::ios::in);
  if(file.is_open()) {
    while (getline(file, m_current_line)) {
      m_current_index = 1;
      next_line();
      m_line++;
    }
  } else {
    cout << "[Error] Can't open file." << endl;
    // TODO exception
  }
}

void Lexer::next_line() {
  while (m_current_index < m_current_line.size()) {
    next_word();
    register_token();
  }
}

void Lexer::next_word() {
  m_token = "";
  char c = m_current_line[m_current_index];
  int i = 0;
  while ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '\'' || c == '"') {
    m_token += c;
    m_current_index++;
    c = m_current_line[m_current_index];
    i++;
  }
  if(i == 0) {
    if(c != ' ') {
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
  if(m_token.size() > 0) {
    Token * t = Token::create(m_token, m_line);
    if(t) {
      m_tokens.push_back(t);
    } else {
      cout << "Syntax error : line " << m_line << endl << m_current_line << endl;
    }
  }
}

vector<Token*> Lexer::get_tokens() const {
  return m_tokens;
}

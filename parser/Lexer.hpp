#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "Token.hpp"

class Lexer {
public:
  Lexer(std::string file_name);

  std::vector<Token*> get_tokens() const;

private:
  void next_word();
  void next_line();
  void register_token();

  std::string m_file_name;
  std::vector<Token*> m_tokens;

  std::string m_current_line;
  unsigned int m_current_index;
  std::string m_token;
  unsigned int m_line;
};

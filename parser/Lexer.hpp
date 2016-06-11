#pragma once

#include <fstream>
#include <iostream>
#include <queue>

#include "../global/Global.hpp"
#include "Token.hpp"
#include "exceptions/LexerException.hpp"

namespace bob {
  class Lexer {
  public:
    Lexer(std::string file_name);

    std::queue<Token*> * get_tokens();

  private:
    void next_word();
    void next_line();
    void register_token();

    std::string m_file_name;
    std::queue<Token*> m_tokens;

    std::string m_current_line;
    unsigned int m_current_index;
    std::string m_token;
    unsigned int m_line;
    unsigned int m_column;
    int m_tmp_col;
  };
};

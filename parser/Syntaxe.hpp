#pragma once

#include <iostream>
#include <vector>

#include "Token.hpp"
#include "../ast/includes.hpp" 

class Syntaxe {
public:
  Syntaxe(std::string& file_name, std::vector<Token*>& tokens);
  
  void analyze_current_token();
  ast::Ast * get_ast() const;

private:
  TokenType getTokenType(unsigned int index);

  std::string m_file_name;
  
  std::vector<Token*> * m_tokens;
  ast::Ast * m_program;
  unsigned int m_index;
};

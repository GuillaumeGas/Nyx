#pragma once

#include <iostream>
#include <vector>

#include "Token.hpp"
#include "../ast/Ast.hpp" 
#include "../ast/Program.hpp"
#include "../ast/Type.hpp"
#include "../ast/VarDecl.hpp"

class Syntaxe {
public:
  Syntaxe(std::string& file_name, std::vector<Token*>& tokens);
  ~Syntaxe();
  
  void analyze_current_token();
  ast::Ast * get_ast() const;

private:
  Token * getToken(unsigned int index);

  std::string m_file_name;
  
  std::vector<Token*> m_tokens;
  ast::Program * m_program;
  unsigned int m_index;
};

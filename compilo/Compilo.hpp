#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "../parser/Token.hpp"
#include "../parser/Lexer.hpp"
#include "../parser/Syntaxe.hpp"
#include "../ast/Ast.hpp"

class Compilo {
public:
  Compilo(std::string file_name);
  ~Compilo();

  void compile();
  void print_tokens() const;
  void print_ast() const;

private:
  Lexer * m_lex;
  Syntaxe * m_syn;

  std::string m_file_name;
  std::vector<Token*> m_tokens;
  ast::Ast * m_ast;
};

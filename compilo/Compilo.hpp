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
  Compilo();
  ~Compilo();

  void compile(std::string file_name);
  void print_tokens() const;
  void print_ast() const;

private:
  std::string m_file_name;
  std::vector<Token*> m_tokens;
  ast::Ast * m_ast;
};

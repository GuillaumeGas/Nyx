#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "Token.hpp"
#include "Lexer.hpp"
//#include "Syntaxe.hpp"

class Compilo {
public:
  Compilo();
  ~Compilo();

  void compile(std::string file_name);
  void print_tokens() const;

private:
  std::string m_file_name;
  std::vector<Token*> m_tokens;
};

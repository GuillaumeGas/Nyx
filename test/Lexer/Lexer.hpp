#pragma once

#include <iostream>
#include <fstream>

struct location_t {
  unsigned int column;
  unsigned int line;
};

struct Token {
  Token (std::string value, location_t loc);
  std::string value;
  location_t loc;
};

struct TokenEof : public Token {
  TokenEof ();
};

enum TokenList {
  SPACE,
  EQ,
  COLON
};

class Lexer {
public:
  Lexer (std::string file_name);
  ~Lexer ();

  Token next ();

private:
  Token getWord ();

  std::string file_name;
  std::string current_line;
  unsigned int current_pos;
  location_t current_loc;
  std::ifstream * file;
};

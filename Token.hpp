#pragma once

#include <iostream>
#include <vector>

enum TokenType {
  NUM,
  CHAR,
  STRING,
  IDENT,
  TYPE,
  ASSIGN,
  PLUS,
  MINUS,
  MUL,
  DIV,
  MOD,
  LT,  // '<'
  LE, // '<='
  GT,  // '>'
  GE, // '>='
  EQ,  // '=='
  NE, // '!='
  PAR_O, // '('
  PAR_C, // ')'
  SEMICOLON, // ';'
  IF,
  ELSE,
  ELSEIF,
  WHILE,
  DO,
  FOR,
  PRINT_I,
  PRINT_S,
  SCAN_I,
  SCAN_S,
};

struct TokenValue {
  virtual std::string to_string() const = 0;
};

struct TokenIntValue : TokenValue {
  TokenIntValue(int i);

  std::string to_string() const;

  int value;
};
struct TokenCharValue : TokenValue  {
  TokenCharValue(char c);

  std::string to_string() const;

  char value;
};
struct TokenStringValue : TokenValue  {
  TokenStringValue(std::string& s);

  std::string to_string() const;

  std::string value;
};

struct Token {
  Token(TokenType t, int v, unsigned int l);
  Token(TokenType t, char c, unsigned int l);
  Token(TokenType t, std::string& s, unsigned int l);
  ~Token();

  std::string to_string() const;
  std::string tokenType_to_string() const;

  TokenType type;
  TokenValue * value;

  unsigned int line;

  static Token* create(std::string token, unsigned int line);
  static bool is_type(std::string t);
  static bool is_ident(std::string t);
  static bool is_assign(std::string t);
  static bool is_number(std::string t);
  static bool is_semicolon(std::string t);
};

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

struct location_t {
    unsigned int column;
    unsigned int line;
};

class Token {
public:
    Token (std::string _value, location_t _loc);
    std::string to_string() const;
    std::string value;
    location_t loc;
};

class TokenEof : public Token {
public:
    TokenEof (location_t _loc);
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

    void setKeys (std::vector<std::string> keys);
    Token next ();
    bool isEof () const;

private:
    Token get_word ();
    std::string read_line (unsigned int offset);

    std::string file_name;
    std::ifstream * file;
    unsigned int current_index;
    location_t current_loc;
    bool eof;
    std::vector<std::string> keys;
};

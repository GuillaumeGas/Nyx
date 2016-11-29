#pragma once

#include <iostream>
#include <cstdio>
#include <vector>

struct location_t {
    unsigned int column;
    unsigned int line;
};

class Token {
public:
    Token (std::string _value, location_t _loc);
    std::string to_string() const;
    bool isEof () const;
    std::string value;
    location_t loc;
    bool eof;
};

class TokenEof : public Token {
public:
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

    void setKeys (std::vector<std::string> keys);
    void setSkips (std::vector<std::string> skips);
    void setComs (std::vector<std::pair<std::string, std::string> > coms);
    Token next ();
    bool isEof () const;

private:
    bool isSkip (Token t) const;
    Token isCom (Token t) const;
    Token get_word ();
    void get_line (std::string & line);
    void mfseek (const std::string & tok, unsigned int offset);

    std::string file_name;
    FILE * file;
    location_t current_loc;
    bool eof;
    std::vector<std::string> keys;
    std::vector<std::string> skips;
    std::vector<std::pair<std::string, std::string> > coms;
};

#pragma once

#include <iostream>

namespace nyx {
  class LexerException {
  public:
    LexerException(const std::string& file_name) throw() : file_name(file_name) {}
    LexerException(const std::string& file_name, unsigned int line, unsigned int column) : file_name(file_name), line(line), column(column) {}
    LexerException(const std::string& file_name, unsigned int line, unsigned int column, std::string& msg) : file_name(file_name), line(line), column(column), msg(msg) {}
    virtual std::string to_string() const {
      return "[!] Error in file " + file_name + ".";
    }
  protected:
    std::string file_name;
    std::string msg;
    unsigned int line;
    unsigned int column;
  };

  class FileNotFoundException : public LexerException {
  public:
    FileNotFoundException(const std::string& file_name) throw() : LexerException(file_name) {}
    std::string to_string() const {
      return "[!] Error : " + file_name + " not found.";
    }
  };

  class TokenErrorException : public LexerException {
  public:
    TokenErrorException(const std::string& file_name, std::string& token, unsigned int line, unsigned int column) throw() : LexerException(file_name, line, column, token) {}
    std::string to_string() const {
      return "[!] Parse error : " + file_name + " (" + std::to_string(line) + "," + std::to_string(column) + ") : unexpected token '" + msg + "'";
    }
  };
};

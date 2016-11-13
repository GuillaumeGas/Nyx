#pragma once

#include <iostream>
#include "../Position.hpp"

namespace nyx {
  class SyntaxException {
  public:
    SyntaxException(syntax::Position& pos) throw() : pos(pos) {}
    virtual std::string to_string() const {
      return "[!] Syntax error " + pos.to_string();
    }
  protected:
    nyx::syntax::Position pos;
  };

  class SyntaxErrorException : public SyntaxException {
  public:
    SyntaxErrorException(const std::string& msg, nyx::syntax::Position pos) throw() : msg(msg), SyntaxException(pos) {}
    std::string to_string() const throw() {
      return "[!] Syntax error, unexpected '" + msg +"' on " + pos.to_string();
    }
  private:
    std::string msg;
  };

  class MissingErrorException : public SyntaxException {
  public:
    MissingErrorException(const std::string& msg, nyx::syntax::Position pos) throw() : SyntaxException(pos), msg(msg) {}
    std::string to_string() const throw() {
      return "[!] Syntax error, expected '" + msg +"' on " + pos.to_string();
    }
  private:
    std::string msg;
  };
};


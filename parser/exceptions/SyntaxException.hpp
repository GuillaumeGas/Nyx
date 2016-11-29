#pragma once

#include <iostream>
#include "../Position.hpp"

namespace nyx {
  class SyntaxException {
  public:
    SyntaxException(syntax::Position& pos) throw() : pos(pos) {}
    virtual std::string toString() const {
      return "[!] Syntax error " + pos.toString();
    }
  protected:
    nyx::syntax::Position pos;
  };

  class SyntaxErrorException : public SyntaxException {
  public:
    SyntaxErrorException(const std::string& msg, nyx::syntax::Position pos) throw() : msg(msg), SyntaxException(pos) {}
    std::string toString() const throw() {
      return "[!] Syntax error, unexpected '" + msg +"' on " + pos.toString();
    }
  private:
    std::string msg;
  };

  class MissingErrorException : public SyntaxException {
  public:
    MissingErrorException(const std::string& msg, nyx::syntax::Position pos) throw() : SyntaxException(pos), msg(msg) {}
    std::string toString() const throw() {
      return "[!] Syntax error, expected '" + msg +"' on " + pos.toString();
    }
  private:
    std::string msg;
  };
};


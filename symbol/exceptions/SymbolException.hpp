#pragma once

#include <iostream>
#include "../../ast/Position.hpp"
#include "../../global/Global.hpp"

namespace nyx {
  class SymbolException {
  public:
    SymbolException(const std::string& file_name, ast::Position * pos) throw() : file_name(file_name), pos(pos) {}
    SymbolException(const std::string& file_name, ast::Position * pos, std::string msg) throw () : file_name(file_name), pos(pos), msg(msg) {}
    virtual std::string toString() const {
      return "[Error] Symbol error in file " + file_name + " at " + pos->toString() + ".\n" + Global::getInstance()->getLine(pos->line);
    }
  protected:
    std::string file_name;
    ast::Position * pos;
    std::string msg;
  };

  class MultipleDefException : public SymbolException {
  public:
    MultipleDefException(const std::string& file_name, ast::Position * pos, std::string msg) throw () : SymbolException (file_name, pos, msg) {}

    std::string toString() const {
      return "[Error] Multiple definitions of " + msg + " at " + pos->toString() + ".\n" + Global::getInstance()->getLine(pos->line);
    }
  };

  class SymbolNotFoundException : public SymbolException {
  public:
    SymbolNotFoundException(const std::string& file_name, ast::Position * pos, std::string msg) throw () : SymbolException (file_name, pos, msg) {}

    std::string toString() const {
      return "[Error] Symbol " + msg + " not found at " + pos->toString() + "." + "\n" + Global::getInstance()->getLine(pos->line);
    }
  };
};

#pragma once

#include <iostream>
#include "../../ast/Position.hpp"
#include "../../global/Global.hpp"

namespace nyx {
  class SymbolException {
  public:
    SymbolException(const std::string& file_name, ast::Position * pos) throw() : file_name(file_name), pos(pos) {}
    SymbolException(const std::string& file_name, ast::Position * pos, std::string msg) throw () : file_name(file_name), pos(pos), msg(msg) {}
    virtual std::string to_string() const {
      return "[Error] Symbol error in file " + file_name + " at " + pos->to_string() + ".\n" + Global::get_instance()->get_line(pos->line);
    }
  protected:
    std::string file_name;
    ast::Position * pos;
    std::string msg;
  };

  class MultipleDefException : public SymbolException {
  public:
    MultipleDefException(const std::string& file_name, ast::Position * pos, std::string& msg) throw () : SymbolException (file_name, pos, msg) {}

    std::string to_string() const {
      return "[Error] Multiple definitions of " + msg + " at " + pos->to_string() + ".\n" + Global::get_instance()->get_line(pos->line);
    }    
  };

  class SymbolNotFoundException : public SymbolException {
  public:
    SymbolNotFoundException(const std::string& file_name, ast::Position * pos, std::string& msg) throw () : SymbolException (file_name, pos, msg) {}

    std::string to_string() const {
      return "[Error] Symbol " + msg + " not found at " + pos->to_string() + "." + "\n" + Global::get_instance()->get_line(pos->line);
    }
  };
};

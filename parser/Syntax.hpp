#pragma once

#include <iostream>
#include <vector>

#include "Token.hpp"
#include "syntax/Program.hpp"
#include "../ast/Ast.hpp" 
#include "../ast/Program.hpp"

namespace bob {
  class Syntax {
  public:
    Syntax(std::string& file_name, std::vector<Token*>& tokens);
    ~Syntax();
  
    ast::Ast * get_ast() const;
    Token * get_token(unsigned int index);
    void add_elem(ast::Ast * elem);

  private:
    std::string m_file_name;
  
    std::vector<Token*> m_tokens;
    ast::Program * m_program;
  };
};

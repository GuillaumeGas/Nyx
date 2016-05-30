#pragma once

#include <iostream>
#include <queue>

#include "Token.hpp"
#include "syntax/Program.hpp"
#include "../ast/Ast.hpp" 
#include "../ast/Program.hpp"

namespace bob {
  class Syntax {
  public:
    Syntax(std::string& file_name, std::queue<Token*> * tokens);
    ~Syntax();
  
    ast::Ast * get_ast() const;
   
    Token * pop();
    void add_elem(ast::Ast * elem);

  private:
    std::string m_file_name;

    std::queue<Token*> * m_tokens; 
    ast::Program * m_program;
  };
};

#pragma once 

#include "Position.hpp"
#include "../Token.hpp"
#include "../../ast/Ast.hpp"
#include "../../ast/Expression.hpp"
#include "../../ast/Binop.hpp"
#include "../../ast/Operator.hpp"
#include "../../ast/ConstInt.hpp"
#include "../../ast/ConstChar.hpp"
#include "../../ast/ConstString.hpp"
#include "../../ast/ConstBool.hpp"
#include "../exceptions/SyntaxException.hpp"

namespace bob {
  class Syntax;
  namespace syntax {
    class Expression {
    public:
      static ast::Expression * analyze(Syntax * syntax);
      static ast::Expression * create_value(Token * token);
      static ast::BinOperator create_operator(Token * token);
    };
  };
};

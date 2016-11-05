#pragma once

#include <iostream>
#include "Expression.hpp"
#include "../Syntax.hpp"
#include "../../ast/VarId.hpp"
#include "../../ast/Binop.hpp"
#include "../../ast/Operator.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class Assign {
	public:
	    static ast::Binop * visit (Syntax * syntax, Token * token_ident, Token * token_op);
	};
    }
}

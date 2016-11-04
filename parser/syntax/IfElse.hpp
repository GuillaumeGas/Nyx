#pragma once

#include <iostream>
#include <queue>

#include "Expression.hpp"
#include "BlocInstruction.hpp"
#include "../Syntax.hpp"
#include "../Token.hpp"
#include "../exceptions/SyntaxException.hpp"
#include "../../ast/Position.hpp"
#include "../../ast/IfElse.hpp"
#include "../../ast/BlocInstruction.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class IfElse {
	public:
	    static ast::IfElse visit (Syntax * syntax, Token * token);
	}
    };
};

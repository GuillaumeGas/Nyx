#pragma once

#include <iostream>
#include "Assign.hpp"
#include "../Token.hpp"
#include "../../ast/Ast.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class Instruction {
	public:
	    static ast::Ast * visit(Syntax * syntax, Token * token_ident);
	};
    };
};

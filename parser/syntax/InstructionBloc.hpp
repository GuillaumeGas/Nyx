#pragma once

#include <iostream>
#include <deque>
#include "Decl.hpp"
#include "Instruction.hpp"
#include "PrintI.hpp"
#include "IfElse.hpp"
#include "../Token.hpp"
#include "../Syntax.hpp"
#include "../../ast/InstructionBloc.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class InstructionBloc {
	public:
	    static ast::InstructionBloc * visit(Syntax * syntax);
	};
    }
}

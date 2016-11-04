#pragma once

#include <iostream>
#include <queue>
#include "Type.hpp"
#include "Ident.hpp"
#include "PrintI.hpp"
#include "IfElse.hpp"
#include "../Token.hpp"
#include "../Syntax.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class BlocInstruction {
	    static ast::BlocInstruction visit(Syntax * syntax);
	};
    }
}

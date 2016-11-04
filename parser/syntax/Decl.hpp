#pragma once

#include <iostream>
#include "../Token.hpp"
#include "../../ast/VarDecl.hpp"
#include "../../ast/Type.hpp"
#include "../../ast/Position.hpp"
#include "Assign.hpp"
#include "VarDecl.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class Decl {
	public:
	    /**
	       Decl := VarDecl | FunDecl
	     */
	    static Ast * visit(Syntax * syntax, Token * type);

	    /**
	       VarDecl := Type Ident (= Expression)?
	     */
	    static Ast * visitVarDecl (Syntax * syntax, Token * type, Token * ident);

	    /**
	       FunDecl := Type Ident (VarDeclr*) { InstructionBloc }
	     */
	    static Ast * visitFunDecl (Syntax * syntax, Token * type, Token * ident);
	};
    };
};

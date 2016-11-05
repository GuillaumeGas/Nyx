#pragma once

#include <iostream>
#include <deque>
#include "Assign.hpp"
#include "../Token.hpp"
#include "../../ast/VarDecl.hpp"
#include "../../ast/Position.hpp"
#include "../../ast/Binop.hpp"

namespace bob {
    class Syntax;
    namespace syntax {
	class Decl {
	public:
	    /**
	       Decl := VarDecl | FunDecl
	     */
	    static ast::Ast * visit(Syntax * syntax, Token * type);

	    /**
	       VarDecl := Type Ident (= Expression)?
	     */
	    static ast::Ast * visitVarDecl (Syntax * syntax, Token * type, Token * ident);

	    /**
	       FunDecl := Type Ident (VarDeclr*) { InstructionBloc }
	     */
	    static ast::Ast * visitFunDecl (Syntax * syntax, Token * type, Token * ident);
	};
    };
};

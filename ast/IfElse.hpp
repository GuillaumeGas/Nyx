#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"

namespace nyx {
    namespace ast {
	typedef InstructionPtr IfElsePtr;

	class IfElse : public Ast {
	public:
	    IfElse (ExpressionPtr cond, BlocPtr bloc_if, Position * pos);
	    IfElse (ExpressionPtr cond, BlocPtr bloc_id, BlocPtr bloc_else, Position * pos);
	    ~IfElse ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    ExpressionPtr cond;
	    BlocPtr bloc_if;
	    BlocPtr bloc_else;
	};
    };
};

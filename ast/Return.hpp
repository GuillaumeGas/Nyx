#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Object.hpp"
#include "Function.hpp"
#include "../global/Position.hpp"
#include "../symbol/Table.hpp"

namespace nyx {
    namespace ast {
	typedef InstructionPtr ReturnPtr;

	class Return : public Instruction {
	public:
	    Return (ExpressionPtr expr, Position * pos);
	    ~Return ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    ExpressionPtr expr;
	};
    };
};

#pragma once

#include <iostream>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	struct UnOp : public Expression {
	    UnOp (Operator * op, Expression * expr, Position * pos);
	    ~UnOp ();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * interpretExpression() {}
	    Expression * interpretPlus (Expression * e) {}
	    Expression * interpretMinus (Expression * e) {}
	    Expression * interpretMul (Expression * e) {}
	    Expression * interpretDiv (Expression * e) {}
	    Expression * interpretMod (Expression * e) {}
	    Expression * interpretAssign (Expression * e) {}

	    Operator * op;
	    Expression * expr;
	};
    };
};

#pragma once

#include <iostream>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Object.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
	struct UnOp : public Expression {
	    UnOp (Operator * op, Expression * expr, Position * pos);
	    ~UnOp ();

	    void print (std::ostream & out, int offset = 0) const;

	    AbstractObject * interpretExpression();

	    Operator * op;
	    Expression * expr;
	};
    };
};

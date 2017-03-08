#pragma once

#include <iostream>

#include "Expression.hpp"
#include "../global/Position.hpp"
#include "Object.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
	typedef ExpressionPtr IndexPtr;

	class Index : public Expression {
	public:
	    Index (ExpressionPtr e1, ExpressionPtr e2, Position * pos);

	    void print (std::ostream & out, int offset = 0) const;

	    ExpressionPtr interpretExpression ();
	    ExpressionPtr interpretASSIGN (ExpressionPtr e);

	    ExpressionPtr e1;
	    ExpressionPtr e2;
	};
    };
};

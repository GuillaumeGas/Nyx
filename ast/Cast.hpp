#pragma once

#include <iostream>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "Object.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
	typedef ExpressionPtr CastPtr;

	class Cast : public Expression {
	public:
	    Cast (Type * type, ExpressionPtr expr, Position * pos);
	    ~Cast ();

	    void print (std::ostream & out, int offset = 0) const;
	    ExpressionPtr interpretExpression ();


	private:
	    Type * type;
	    ExpressionPtr expr;
	};
    };
};

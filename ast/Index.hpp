#pragma once

#include <iostream>

#include "Expression.hpp"
#include "Position.hpp"
#include "Object.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
	class Index : public Expression {
	public:
	    Index (Expression * e1, Expression * e2, Position * pos);
	    ~Index ();

	    void print (std::ostream & out, int offset = 0) const;

	    AbstractObject * interpretExpression ();
	    AbstractObject * interpretASSIGN (AbstractObject * e);

	    Expression * e1;
	    Expression * e2;
	};
    };
};

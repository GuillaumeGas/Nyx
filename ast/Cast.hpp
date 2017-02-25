#pragma once

#include <iostream>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "Expression.hpp"
#include "Object.hpp"

namespace nyx {
    namespace ast {
	class Cast : public Expression {
	public:
	    Cast (Type * type, Expression * expr, Position * pos);
	    ~Cast ();

	    void print (std::ostream & out, int offset = 0) const;
	    AbstractObject * interpretExpression ();


	private:
	    Type * type;
	    Expression * expr;
	};
    };
};

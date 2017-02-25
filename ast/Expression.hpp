#pragma once

#include <iostream>
#include <memory>

#include "Ast.hpp"

namespace nyx {
    namespace ast {
	class AbstractObject;
	class Expression;

	typedef std::shared_ptr<Expression> ExpressionPtr;

	class Expression : public Ast {
	public:
	    virtual void print (std::ostream & out, int offset = 0) const = 0;
	    virtual AbstractObject * interpretExpression () = 0;

	    static ExpressionPtr make (Expression * expr);
	};
    };
};

#pragma once

#include <iostream>
#include <iomanip>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	struct Binop : public Expression {
	    Binop(Expression * e1, Expression * e2, Operator * op, Position * pos);
	    ~Binop();

	    Expression * interpretExpression ();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * e1;
	    Expression * e2;
	    Operator * op;
	};
    };
};

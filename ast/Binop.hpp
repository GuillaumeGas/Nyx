#pragma once

#include <iostream>
#include <iomanip>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Object.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	typedef ExpressionPtr BinopPtr;
	
	struct Binop : public Expression {
	    Binop(ExpressionPtr e1, ExpressionPtr e2, Operator * op, Position * pos);
	    ~Binop();

	    ExpressionPtr interpretExpression ();
	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	    ExpressionPtr e1;
	    ExpressionPtr e2;
	    Operator * op;
	};
    };
};

#pragma once

#include <iostream>
#include <ostream>
#include "Binop.hpp"
#include "Expression.hpp"
#include "VarId.hpp"
#include "Operator.hpp"
#include "Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	class VarAssign : public Binop {
	public:
	    VarAssign (VarId * e1, Expression * e2, Operator * op, Position * pos);
	    virtual ~VarAssign ();

	    Expression * interpretExpression ();

	    void print (std::ostream & out, int offset = 0) const;
	};
    };
};

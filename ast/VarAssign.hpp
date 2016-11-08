#pragma once

#include <iostream>
#include <ostream>
#include "Binop.hpp"
#include "Expression.hpp"
#include "Operator.hpp"
#include "Position.hpp"

namespace bob {
    namespace ast {
	class VarAssign : public Binop {
	public:
	    VarAssign (Expression * e1, Expression * e2, Operator * op, Position * pos);
	    virtual ~VarAssign ();

	    void print (std::ostream & out, int offset = 0) const;
	};
    };
};

#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Value.hpp"
#include "Type.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	struct ConstFloat : public Expression {
	    ConstFloat (float value, Position * pos);
	    ~ConstFloat ();

	    void print (std::ostream & out, int offset = 0) const;
	};
    };
};

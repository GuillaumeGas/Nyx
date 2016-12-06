#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"

namespace nyx {
    namespace ast {
	struct ConstString : public Expression {
	    ConstString (const std::string & value, Position * pos);
	    ~ConstString ();

	    void print (std::ostream & out, int offset = 0) const;
	};
    };
};

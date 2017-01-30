#pragma once

#include <iostream>

#include "Ast.hpp"

namespace nyx {
    namespace ast {
	class AbstractObject;
	class Expression : public Ast {
	public:
	    virtual void print (std::ostream & out, int offset = 0) const = 0;
	    virtual AbstractObject * interpretExpression () = 0;
	};
    };
};

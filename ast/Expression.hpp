#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Type.hpp"
#include "Value.hpp"

namespace nyx {
    namespace ast {
	class Expression : public Ast {
	public:
	    Expression();
	    virtual ~Expression();
	    virtual void print (std::ostream & out, int offset = 0) const = 0;
	    void interpret ();
	    virtual Expression * interpretExpression();
	    virtual Expression * interpretPlus (Expression * e) {}
	    virtual Expression * interpretMinus (Expression * e) {}
	    virtual Expression * interpretMul (Expression * e) {}
	    virtual Expression * interpretDiv (Expression * e) {}
	    virtual Expression * interpretMod (Expression * e) {}
	    virtual Expression * interpretAssign (Expression * e) {}

	    virtual Type * getType () const;
	    virtual Value * getValue () const;

	    Type * type;
	    Value * value;
	};
    };
};

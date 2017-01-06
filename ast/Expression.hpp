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
	    virtual Value interpretExpression() { return Value (); }
	    virtual Value interpretPlus (Expression * e) { return Value (); }
	    virtual Value interpretMinus (Expression * e) { return Value (); }
	    virtual Value interpretMul (Expression * e) { return Value (); }
	    virtual Value interpretDiv (Expression * e) { return Value (); }
	    virtual Value interpretMod (Expression * e) { return Value (); }
	    virtual Value interpretAssign (Expression * e) { return Value (); }

	    virtual Value * getValue () const;

	    Value * value;
	};
    };
};

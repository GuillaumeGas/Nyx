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
	    virtual Expression * interpretExpr();
	    virtual Expression * sum(Expression * expr);
	    virtual void interpret();

	    Type * getType() const;

	    virtual Value * getValue() const;

	    //	private:
	    Type * type;
	    Value * value;
	};
    };
};

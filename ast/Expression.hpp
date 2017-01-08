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

	    virtual Expression * clone ();
	    virtual Expression * interpretExpression();
	    virtual Expression * interpretASSIGN (Expression * e);
	    virtual Expression * interpretLE (Expression * e);
	    virtual Expression * interpretGE (Expression * e);
	    virtual Expression * interpretNE (Expression * e);
	    virtual Expression * interpretPLUSEQ (Expression * e);
	    virtual Expression * interpretMINUSEQ (Expression * e);
	    virtual Expression * interpretMULEQ (Expression * e);
	    virtual Expression * interpretDIVEQ (Expression * e);
	    virtual Expression * interpretMODEQ (Expression * e);
	    virtual Expression * interpretLT (Expression * e);
	    virtual Expression * interpretGT (Expression * e);
	    virtual Expression * interpretEQ (Expression * e);
	    virtual Expression * interpretAND (Expression * e);
	    virtual Expression * interpretOR (Expression * e);
	    virtual Expression * interpretPLUS (Expression * e);
	    virtual Expression * interpretMINUS (Expression * e);
	    virtual Expression * interpretMUL (Expression * e);
	    virtual Expression * interpretDIV (Expression * e);
	    virtual Expression * interpretMOD (Expression * e);
	    virtual Expression * interpretPOINT (Expression * e);

	    virtual Expression * interpretUnaryMINUS ();

	    virtual Value * getValue () const;

	    Value * value;
	};
    };
};

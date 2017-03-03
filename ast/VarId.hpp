
#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"
#include "Expression.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "Object.hpp"
#include "Operator.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
	typedef ExpressionPtr VarIdPtr;

	class VarId : public Expression {
	public:
	    VarId (std::string name, Position * pos);
	    VarId (std::string name, ExpressionPtr ptr, Position * pos);
	    ~VarId ();

	    void print (std::ostream & out, int offset = 0) const;

	    bool getBool () const;
	    int getInt () const;
	    char getChar () const;
	    float getFloat () const;
	    std::vector<ExpressionPtr> * getArray () const;
	    ExpressionPtr getRangeBegin () const;
	    ExpressionPtr getRangeEnd () const;
	    // Object * getObject () const;

	    ExpressionPtr clone ();
	    ExpressionPtr interpretExpression ();
	    ExpressionPtr interpretASSIGN (ExpressionPtr e);
	    ExpressionPtr interpretLE (ExpressionPtr e);
	    ExpressionPtr interpretGE (ExpressionPtr e);
	    ExpressionPtr interpretNE (ExpressionPtr e);
	    ExpressionPtr interpretLT (ExpressionPtr e);
	    ExpressionPtr interpretGT (ExpressionPtr e);
	    ExpressionPtr interpretEQ (ExpressionPtr e);
	    ExpressionPtr interpretAND (ExpressionPtr e);
	    ExpressionPtr interpretOR (ExpressionPtr e);
	    ExpressionPtr interpretPLUS (ExpressionPtr e);
	    ExpressionPtr interpretMINUS (ExpressionPtr e);
	    ExpressionPtr interpretMUL (ExpressionPtr e);
	    ExpressionPtr interpretDIV (ExpressionPtr e);
	    ExpressionPtr interpretMOD (ExpressionPtr e);

	    ExpressionPtr interpretUnaryMINUS ();

	    std::string name;
	private:
	    ExpressionPtr value;

	    ExpressionPtr _interpretBinop (Op op, ExpressionPtr e);
	};
    };
};

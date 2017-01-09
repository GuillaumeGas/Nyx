#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"
#include "Const.hpp"
#include "Operator.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	class VarId : public Expression {
	public:
	    VarId(std::string name, Position * pos);
	    ~VarId();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    Expression * interpretExpression();
	    Expression * interpretASSIGN (Expression * e);
	    Expression * interpretLE (Expression * e);
	    Expression * interpretGE (Expression * e);
	    Expression * interpretNE (Expression * e);
	    Expression * interpretLT (Expression * e);
	    Expression * interpretGT (Expression * e);
	    Expression * interpretEQ (Expression * e);
	    Expression * interpretAND (Expression * e);
	    Expression * interpretOR (Expression * e);
	    Expression * interpretPLUS (Expression * e);
	    Expression * interpretMINUS (Expression * e);
	    Expression * interpretMUL (Expression * e);
	    Expression * interpretDIV (Expression * e);
	    Expression * interpretMOD (Expression * e);

	    Expression * interpretUnaryMINUS ();

	    std::string name;
	private:
	    Expression * _interpretBinop (Op op, Expression * e);
	    Expression * _interpretOp (Op op, Expression * e1, Expression * e2);
	};
    };
};

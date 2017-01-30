#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Object.hpp"
#include "Operator.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	class VarId : public AbstractObject {
	public:
	    VarId (std::string name, Position * pos);
	    VarId (std::string name, AbstractObject * ptr, Position * pos);
	    ~VarId ();

	    void print (std::ostream & out, int offset = 0) const;

	    bool getBool () const;
	    int getInt () const;
	    char getChar () const;
	    float getFloat () const;
	    std::vector<Expression*> * getArray () const;
	    AbstractObject * getRangeStart () const;
	    AbstractObject * getRangeEnd () const;
	    // Object * getObject () const;
	    AbstractObject * getPtr ();

	    Expression * clone ();
	    AbstractObject * interpretExpression ();
	    AbstractObject * interpretASSIGN (AbstractObject * e);
	    AbstractObject * interpretLE (AbstractObject * e);
	    AbstractObject * interpretGE (AbstractObject * e);
	    AbstractObject * interpretNE (AbstractObject * e);
	    AbstractObject * interpretLT (AbstractObject * e);
	    AbstractObject * interpretGT (AbstractObject * e);
	    AbstractObject * interpretEQ (AbstractObject * e);
	    AbstractObject * interpretAND (AbstractObject * e);
	    AbstractObject * interpretOR (AbstractObject * e);
	    AbstractObject * interpretPLUS (AbstractObject * e);
	    AbstractObject * interpretMINUS (AbstractObject * e);
	    AbstractObject * interpretMUL (AbstractObject * e);
	    AbstractObject * interpretDIV (AbstractObject * e);
	    AbstractObject * interpretMOD (AbstractObject * e);

	    AbstractObject * interpretUnaryMINUS ();

	    std::string name;
	private:
	    AbstractObject * value;

	    AbstractObject * _interpretBinop (Op op, AbstractObject * e);
	};
    };
};

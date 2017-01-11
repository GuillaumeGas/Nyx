#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
	class Int : public Expression {
	public:
	    Int(int value, Position * pos);
	    ~Int();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    Expression * interpretExpression();
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
	};

	class Char : public Expression {
	public:
	    Char(char value, Position * pos);
	    ~Char();
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    Expression * interpretExpression ();
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
	};

	struct Float : public Expression {
	    Float (float value, Position * pos);
	    ~Float ();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    Expression * interpretExpression ();
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

	    Expression * interpretUnaryMINUS ();
	};

	class Bool : public Expression {
	public:
	    Bool(bool value, Position * pos);
	    ~Bool();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    Expression * interpretExpression ();
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
	};

	struct Array : public Expression {
	    Array ();
	    Array (std::vector<Expression*> * array, Position * pos);
	    ~Array ();

	    Expression * clone ();
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * interpretExpression ();
	    // Expression * interpretAND (Expression * e);
	    // Expression * interpretOR (Expression * e);
	    Expression * interpretPLUS (Expression * e);

	    std::vector<Expression*> * array;
	};

	struct String : public Array {
	    String (std::string str, Position * pos);
	    String (const String & str, Position * pos);

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * interpretExpression ();
	};

	struct Range : public Expression {
	    Range (Expression * start, Expression * end, Position * pos);
	    ~Range ();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    Expression * interpretExpression ();

	    Expression * start;
	    Expression * end;
	};
    };
};

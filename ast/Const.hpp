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

	    Expression * interpretExpression();
	    Expression * interpretPlus (Expression * e);
	    Expression * interpretMinus (Expression * e) {}
	    Expression * interpretMul (Expression * e) {}
	    Expression * interpretDiv (Expression * e) {}
	    Expression * interpretMod (Expression * e) {}
	    Expression * interpretAssign (Expression * e) {}
	};

	class Char : public Expression {
	public:
	    Char(char value, Position * pos);
	    ~Char();
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * interpretExpression();
	    Expression * interpretPlus (Expression * e);
	    Expression * interpretMinus (Expression * e) {}
	    Expression * interpretMul (Expression * e) {}
	    Expression * interpretDiv (Expression * e) {}
	    Expression * interpretMod (Expression * e) {}
	    Expression * interpretAssign (Expression * e) {}

	};

	struct Float : public Expression {
	    Float (float value, Position * pos);
	    ~Float ();

	    void print (std::ostream & out, int offset = 0) const;
	};

	class Bool : public Expression {
	public:
	    Bool(bool value, Position * pos);
	    ~Bool();

	    void print (std::ostream & out, int offset = 0) const;
	};

	struct String : public Expression {
	    String (std::string * value, Position * pos);
	    ~String ();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * interpretExpression();
	};

	struct Array : public Expression {
	    Array (std::vector<Expression*> * array, Position * pos);
	    ~Array ();

	    void print (std::ostream & out, int offset = 0) const;

	    std::vector<Expression*> * array;
	};

	struct Range : public Expression {
	    Range (Expression * start, Expression * end, Position * pos);
	    ~Range ();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * start;
	    Expression * end;
	};
    };
};

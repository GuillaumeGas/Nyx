#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"

namespace nyx {
    namespace ast {
	class ConstInt : public Expression {
	public:
	    ConstInt(int value, Position * pos);
	    ~ConstInt();

	    void print (std::ostream & out, int offset = 0) const;
	    Expression * interpret_expr();

	    Expression * sum(Expression * expr);
	};

	class ConstChar : public Expression {
	public:
	    ConstChar(char value, Position * pos);
	    ~ConstChar();
	    void print (std::ostream & out, int offset = 0) const;
	};

	struct ConstFloat : public Expression {
	    ConstFloat (float value, Position * pos);
	    ~ConstFloat ();

	    void print (std::ostream & out, int offset = 0) const;
	};

	class ConstBool : public Expression {
	public:
	    ConstBool(bool value, Position * pos);
	    ~ConstBool();

	    void print (std::ostream & out, int offset = 0) const;
	};

	struct ConstString : public Expression {
	    ConstString (std::string * value, Position * pos);
	    ~ConstString ();

	    void print (std::ostream & out, int offset = 0) const;
	};

    };
};

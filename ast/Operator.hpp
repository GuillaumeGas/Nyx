#pragma once

#include <iostream>

namespace nyx {
    namespace ast {

	enum OpPriority {
	    UUULOW_OP,
	    UULOW_OP,
	    ULOW_OP,
	    LOW_OP,
	    HIGH_OP
	};

	enum Op {
	    PLUS,
	    MINUS,
	    MUL,
	    DIV,
	    MOD,
	    ASSIGN,
	    LT,
	    LE,
	    GT,
	    GE,
	    EQ,
	    NE,
	    UNKNOWN
	};

	class Operator {
	public:
	    Operator (std::string s);
	    Operator (const Operator & op);
	    OpPriority priority;
	    Op value;

	    std::string toString() const;

	private:
	    Op getValue(std::string s);
	    OpPriority getPriority(Op o);
	};

    };
};

#pragma once

#include <iostream>

namespace nyx {
    namespace ast {
	enum Op {
	    PLUSPLUS,
	    MINUSMINUS,
	    POINT,
	    NOT,
	    PLUS,
	    MINUS,
	    MUL,
	    DIV,
	    MOD,
	    MULEQ,
	    DIVEQ,
	    PLUSEQ,
	    MINUSEQ,
	    MODEQ,
	    ASSIGN,
	    LT,
	    LE,
	    GT,
	    GE,
	    EQ,
	    NE,
	    AND,
	    OR,
	    UNKNOWN
	};

	class Operator {
	public:
	    Operator (std::string s);
	    Operator (const Operator & op);
	    Op value;

	    std::string toString() const;
	    static Op getValue(std::string s);

	private:
	    std::string str;
	};

    };
};

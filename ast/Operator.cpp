#include "Operator.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Operator::Operator(string s) {
    str = s;
    value = getValue(s);
}

Operator::Operator (const Operator & op) {
    str = op.str;
    value = op.value;
}

string Operator::toString() const {
    return str;
}

Op Operator::getValue(string s) {
    if (s == "+") {
	return Op::PLUS;
    } else if(s == "++") {
	return Op::PLUSPLUS;
    } else if (s == "-") {
	return Op::MINUS;
    } else if (s == "--") {
	return Op::MINUSMINUS;
    } else if (s == "*") {
	return Op::MUL;
    } else if (s == "/") {
	return Op::DIV;
    } else if (s == "%") {
	return Op::MOD;
    } else if (s == "*=") {
	return Op::MULEQ;
    } else if (s == "/=") {
	return Op::DIVEQ;
    } else if (s == "+=") {
	return Op::PLUSEQ;
    } else if (s == "-=") {
	return Op::MINUSEQ;
    } else if (s == "%=") {
	return Op::MODEQ;
    } else if (s == "=") {
	return Op::ASSIGN;
    } else if (s == "<") {
	return Op::LT;
    } else if (s == "<=") {
	return Op::LE;
    } else if (s == ">") {
	return Op::GT;
    } else if (s == ">=") {
	return Op::GE;
    } else if (s == "==") {
	return Op::EQ;
    } else if (s == "!=") {
	return Op::NE;
    } else if (s == "&&") {
	return Op::AND;
    } else if (s == "||") {
	return Op::OR;
    } else if (s == "!") {
	return Op::NOT;
    } else if (s == "[") {
	return Op::INDEX;
    } else {
	return Op::UNKNOWN;
    }
}

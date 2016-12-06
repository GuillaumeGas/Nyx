#include "Operator.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Operator::Operator(string s) {
    value = getValue(s);
    priority = getPriority(value);
}

Operator::Operator (const Operator & op) {
    value = op.value;
    priority = op.priority;
}

string Operator::toString() const {
    switch (value) {
    case PLUS:
	return "+";
	break;
    case MINUS:
	return "-";
	break;
    case MUL:
	return "*";
	break;
    case DIV:
	return "/";
	break;
    case MOD:
	return "%";
	break;
    case ASSIGN:
	return "=";
	break;
    case LT:
	return "<";
	break;
    case LE:
	return "<=";
	break;
    case GT:
	return ">";
	break;
    case GE:
	return ">=";
	break;
    case EQ:
	return "==";
	break;
    case NE:
	return "!=";
	break;
    default:
	return "?";
    }
}

Op Operator::getValue(string s) {
    if (s == "+") {
	return Op::PLUS;
    } else if (s == "-") {
	return Op::MINUS;
    } else if (s == "*") {
	return Op::MUL;
    } else if (s == "/") {
	return Op::DIV;
    } else if (s == "%") {
	return Op::MOD;
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
    } else {
	return Op::UNKNOWN;
    }
}

OpPriority Operator::getPriority(Op o) {
    switch (o) {
    case Op::MUL:
    case Op::DIV:
    case Op::MOD:
	return OpPriority::HIGH_OP;
	break;
    case Op::PLUS:
    case Op::MINUS:
	return OpPriority::LOW_OP;
	break;
    case Op::GT:
    case Op::LT:
	return OpPriority::ULOW_OP;
	break;
    default:
	return OpPriority::UUULOW_OP;
    }
}

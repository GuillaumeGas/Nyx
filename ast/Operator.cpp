#include "Operator.hpp"

using namespace std;
using namespace ast;

Operator::Operator(string s) {
  value = get_value(s);
  priority = get_priority(value);
}

string Operator::to_string() const {
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
  default:
    return "?";
  }  
}

Op Operator::get_value(string s) {
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
  }
}

OpPriority Operator::get_priority(Op o) {
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
  }
}

#pragma once

namespace ast {
  enum BinOperator {
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD
  };

  struct Operator {
    static std::string to_string(BinOperator op) {
      switch (op) {
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
  };
};

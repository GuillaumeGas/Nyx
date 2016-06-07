#include "Type.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Type::Type(string name, bool is_basic) : name(name), is_basic(is_basic) {}

Type::~Type() {  }

string Type::to_string() const {
  return name;
}

TYPE Type::get_type() const {
  if (name == "int") {
    return TYPE::INT;
  } else if (name == "char") {
    return TYPE::CHAR;
  } else if (name == "string") {
    return TYPE::STRING;
  } else {
    return TYPE::ERR;
  }
}

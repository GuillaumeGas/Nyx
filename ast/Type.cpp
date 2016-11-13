#include "Type.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Type::Type(string name, bool is_basic) : name(name), is_basic(is_basic) {
  type = get_type();
}

Type::~Type() {  }

string Type::to_string() const {
  return name;
}

TYPE Type::get_type() const {
  if (name == "int") {
    return TYPE::INT;
  } else if (name == "char") {
    return TYPE::CHAR;
  } else {
    return TYPE::ERR;
  }
}

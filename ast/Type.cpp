#include "Type.hpp"

using namespace std;
using namespace ast;

Type::Type(string name, bool is_basic) : name(name), is_basic(is_basic) {}

Type::~Type() {  }

string Type::to_string() const {
  return name;
}

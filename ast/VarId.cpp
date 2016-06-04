#include "VarId.hpp"

using namespace std;
using namespace bob;
using namespace ast;

VarId::VarId(string name, Position * pos) : name(name) {
  this->pos = pos;
}

VarId::~VarId() {}

string VarId::to_string() const {
  return name;
}

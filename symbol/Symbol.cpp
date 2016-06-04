#include "Symbol.hpp"

using namespace std;
using namespace bob;
using namespace symbol;

Symbol::Symbol(string name) : name(name) {}

string Symbol::to_string() const {
  return "symbol " + name;
}

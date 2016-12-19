#include "Value.hpp"

using namespace nyx;
using namespace ast;

Value * Value::makeValue () {
    Value * val = new Value ();
    memset (val, 0, sizeof (Value));
    return val;
}

#include "VarAssign.hpp"

using namespace std;
using namespace bob;
using namespace ast;

VarAssign::VarAssign (Expression * e1, Expression * e2, Operator * op, Position * pos) : Binop (e1, e2, op, pos) {}

VarAssign::~VarAssign () {}

string VarAssign::to_string() const {
    return "VarAssign " + Binop::to_string() + "\n";
}

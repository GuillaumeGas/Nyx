#include "VarAssign.hpp"

using namespace std;
using namespace bob;
using namespace ast;

VarAssign::VarAssign (Expression * e1, Expression * e2, Operator * op, Position * pos) : Binop (e1, e2, op, pos) {}

VarAssign::~VarAssign () {}

void VarAssign::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "VarAssign ";
    Binop::print (out);
    out << endl;
}

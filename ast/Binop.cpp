#include "Binop.hpp"

using namespace std;
using namespace ast;

Binop::Binop(Expression * e1, Expression * e2, Operator * op, Position * pos) : e1(e1), e2(e2), op(op) {
  this->pos = pos;
}

Binop::~Binop() {
  if (e1)
    delete e1;
  if (e2)
    delete e2;
  if (op)
    delete op;
}

string Binop::to_string() const {
  return "(" + e1->to_string() + " " + op->to_string() + " " + e2->to_string() + ")";
}

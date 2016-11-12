#include "Break.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Break::Break (string * ident, Position * pos) {
  this->ident = ident;
  this->pos = pos;
}

Break::~Break () {
  if (ident)
    delete ident;
}

void Break::interpret () {}

void Break::print (ostream & out, int offset) const {
  shift (out, offset);
  out << "Break";
  if (ident)
    out << " " << *ident;
}

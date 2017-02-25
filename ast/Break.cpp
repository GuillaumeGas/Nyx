#include "Break.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Break::Break (string * ident, Position * pos) {
  this->ident = ident;
  this->pos = pos;
}

Break::~Break () {
  if (ident)
    delete ident;
}

void Break::secondPass () {}

void Break::print (ostream & out, int offset) const {
  shift (out, offset);
  out << "Break";
  if (ident)
    out << " " << *ident;
}

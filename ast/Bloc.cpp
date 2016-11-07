#include "Bloc.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Bloc::Bloc(vector<Ast*> * content) {
  pos = new Position(0, 0);
  this->content = content;
}

Bloc::~Bloc() {
  for(Ast* a : *content) {
    if (a) {
      delete a;
    }
  }
}

void Bloc::interpret() {
  for (Ast * a : *content) {
    a->interpret();
  }
}

string Bloc::to_string() const {
  string res = "";
  for(Ast* a : *content) {
    res += a->to_string() + "\n";
  }
  return res;
}

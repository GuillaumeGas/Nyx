#include "VarAssign.hpp"

using namespace std;
using namespace bob;
using namespace ast;

VarAssign::VarAssign(string var_name, Expression * value, Position * pos) : name(var_name), value(value) {
  this->pos = pos;
}

VarAssign::~VarAssign() {
  if (value)
    delete value;
}

void VarAssign::interpret() {
  symbol::Table * table = symbol::Table::get_instance();
  
  symbol::Symbol * s = table->get_symbol(name, this->pos);
  
  // TODO : interpret de l'expression renvoie une valeur symbol::Value (type + valeur)
  // checker si les types correspondent
  // exception ou maj du symbole en mémoire
}

string VarAssign::to_string() const {
  string res = "";
  res += "VarAssign " + name + " " + value->to_string() + ", " + pos->to_string();
  return res;
}

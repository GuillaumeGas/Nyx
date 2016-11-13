#include "Scope.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Scope::Scope(Scope * parent) {
  parent_scope = parent;
  next_scope = NULL;
}

Scope::~Scope() {
  if (next_scope)
    delete next_scope;

  for (auto it = list.begin(); it != list.end(); it++) 
    delete it->second;
}

Scope * Scope::new_scope() {
  if (next_scope) {
    cout << "[Error] Next scope already exist." << endl;
    exit(-1);
  }
  next_scope = new Scope(this);
  return next_scope;
}

Scope * Scope::get_parent() {
  return parent_scope;
}

void Scope::add_symbol(Symbol * s, ast::Position * pos) {
  if (list.find(s->name) != list.end()) {
    throw MultipleDefException(Global::get_instance()->file_name, pos, s->name);
    exit(-1);
  }
  list[s->name] = s;
}

Symbol * Scope::get_symbol(string name, ast::Position * pos) {
  auto it = list.find(name);
  if (it != list.end()) 
    return it->second;
  throw SymbolNotFoundException(Global::get_instance()->file_name, pos, name);
  exit(-1);
}

string Scope::to_string() const {
  string res = "";
  for (auto it = list.begin(); it != list.end(); it++) 
     res += it->second->to_string() + "\n";
  if (next_scope)
    res += next_scope->to_string();
  return res;
}

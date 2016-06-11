#include "Table.hpp"

using namespace std;
using namespace bob;
using namespace symbol;

Table * Table::instance = NULL;

Table::Table() { current_scope = &main_scope; }
Table::~Table() {}

Table * Table::get_instance() {
  if (instance == NULL)
    instance = new Table;
  return instance;
}

void Table::enter_block() {
  current_scope = current_scope->new_scope();
}

void Table::exit_block() {
  Scope * tmp = current_scope->get_parent();
  if (tmp) {
    delete current_scope;
    current_scope = tmp;
  } else {
    cout << "[Error] Cannot exit block." << endl;
    exit(-1);
  }
}

void Table::add_symbol(Symbol * s, ast::Position * pos) {
  current_scope->add_symbol(s, pos);
}

Symbol * Table::get_symbol(string name, ast::Position * pos) {
  current_scope->get_symbol(name, pos);
}

string Table::to_string() const {
  return current_scope->to_string();
}

// #include "VarAssign.hpp"

// using namespace std;
// using namespace bob;
// using namespace ast;

// VarAssign::VarAssign(string var_name, Expression * value, Position * pos) : name(var_name), value(value) {
//   this->pos = pos;
// }

// VarAssign::~VarAssign() {
//   if (value)
//     delete value;
// }

// void VarAssign::interpret() {
//   symbol::Table * table = symbol::Table::get_instance();
  
//   symbol::Symbol * s = table->get_symbol(name, this->pos);
//   Expression * right = value->interpret_expr();
  
//   if (s->get_type()->type != right->type->type)
//     throw TypeErrorException(s->get_type(), right->type, pos);

//   s->set_value(right->get_value());
// }

// string VarAssign::to_string() const {
//   string res = "";
//   res += "VarAssign " + name + " " + value->to_string() + ", " + pos->to_string();
//   return res;
// }

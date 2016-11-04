#include "Binop.hpp"

using namespace std;
using namespace bob;
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

Expression * Binop::interpret_expr() {
    e1 = e1->interpret_expr();
    e2 = e2->interpret_expr();
    if (check_compatibility()) {
	switch (op->value) {
	case Op::PLUS:
	    return interpret_plus();
	case Op::MINUS:
	    return interpret_minus();
	case Op::MUL:
	    return interpret_mul();
	case Op::DIV:
	    return interpret_div();
	case Op::MOD:
	    return interpret_mod();
	case Op::ASSIGN:
	    return interpret_assign();
	}
    } else {
	throw TypeErrorException(e1, e2, pos);
    }
}

/* TODO, version de test ici */
bool Binop::check_compatibility() const {
    return e1->get_type()->get_type() == e2->get_type()->get_type();
}

Expression * Binop::interpret_plus() {
    if (e1->type->is_basic) {
	cout << "sum..." << endl;
	return e1->sum(e2);
    } else {
	//TODO
    }
}
Expression * Binop::interpret_minus() { return NULL; }
Expression * Binop::interpret_mul() { return NULL; }
Expression * Binop::interpret_div() { return NULL; }
Expression * Binop::interpret_mod() { return NULL; }

Expression * Binop::interpret_assign() {
    symbol::Table * table = symbol::Table::get_instance();

    symbol::Symbol * s = table->get_symbol (e1->to_string(), e1->pos);
    if (e2->get_type()->get_type() == TYPE::INT) {
	s->set_value (e2->get_value()->Int);
    }
}

string Binop::to_string() const {
    return "Binop(" + e1->to_string() + " " + op->to_string() + " " + e2->to_string() + ")";
}

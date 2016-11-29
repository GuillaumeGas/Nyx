#include "Binop.hpp"

using namespace std;
using namespace nyx;
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

Expression * Binop::interpretExpr() {
    e1 = e1->interpretExpr();
    e2 = e2->interpretExpr();
    if (checkCompatibility()) {
	switch (op->value) {
	case Op::PLUS:
	    return interpretPlus();
	case Op::MINUS:
	    return interpretMinus();
	case Op::MUL:
	    return interpretMul();
	case Op::DIV:
	    return interpretDiv();
	case Op::MOD:
	    return interpretMod();
	case Op::ASSIGN:
	    return interpretAssign();
	}
    } else {
	throw TypeErrorException(e1, e2, pos);
    }
}

/* TODO, version de test ici */
bool Binop::checkCompatibility() const {
    return e1->getType()->getType() == e2->getType()->getType();
}

Expression * Binop::interpretPlus() {
    if (e1->type->isBasic()) {
	return e1->sum(e2);
    } else {
	//TODO
    }
}
Expression * Binop::interpretMinus() { return NULL; }
Expression * Binop::interpretMul() { return NULL; }
Expression * Binop::interpretDiv() { return NULL; }
Expression * Binop::interpretMod() { return NULL; }

Expression * Binop::interpretAssign() {
    // symbol::Table * table = symbol::Table::get_instance();

    // symbol::Symbol * s = table->get_symbol (e1->to_string(), e1->pos);
    // if (e2->get_type()->get_type() == TYPE::INT) {
    // 	s->set_value (e2->get_value()->Int);
    // }
}

void Binop::print (ostream & out, int offset) const {
    out << "Binop(";
    e1->print (out);
    out << " " << op->toString() << " ";
    e2->print (out);
    out << ")";
}

#include "Object.hpp"
#include "exceptions/SemanticException.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bool::Bool(bool value, Position * pos) {
    this->pos = pos;
    this->type = new Type ("bool");
    this->value = value;
}

Bool::~Bool() {}

bool Bool::getBool () const { return value; }

void Bool::print (ostream & out, int offset) const {
    out << "ConstBool(" << (value ? "true" : "false") << ")";
}

ExpressionPtr Bool::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return Expression::New<Bool> (value, new_pos);
}

ExpressionPtr Bool::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value <= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;
    
    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value >= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value != e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value < e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value > e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value == e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value && e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value || e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value + e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value + e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value + e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value + e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value - e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value - e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value - e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value - e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value * e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value * e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value * e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value * e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value / e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value / e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value / e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value / e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Bool::interpretMOD (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value / e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value / e->getChar (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}


ExpressionPtr Bool::interpretUnaryMINUS () {
    return Expression::New<Bool> (value * -1, NULL_POSITION);
}


// ####################################

Char::Char(char value, Position * pos) {
    this->pos = pos;
    this->type = new Type ("char");
    this->value = value;
}

Char::~Char() {}

char Char::getChar () const { return value; }

void Char::print (ostream & out, int offset) const {
    out << "ConstChar(" << "'" << value << "'" << ")";
}

ExpressionPtr Char::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return Expression::New<Char> (value, new_pos);
}

ExpressionPtr Char::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value <= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value >= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value != e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value < e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value > e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value == e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value && e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value || e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value + e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value + e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value + e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value + e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value - e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value - e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value - e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value - e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value * e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value * e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value * e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value * e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value / e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value / e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value / e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value / e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Char::interpretMOD (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return Expression::New<Char> (value % e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value % e->getChar (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}


ExpressionPtr Char::interpretUnaryMINUS () {
    return Expression::New<Char> (value * -1, NULL_POSITION);
}

// ####################################

Int::Int(int v, Position * pos) {
    this->pos = pos;
    this->value = v;
    this->type = new Type ("int");
}

Int::~Int() { }

int Int::getInt () const { return value; }

void Int::setInt (int v) { value = v; }

void Int::print (ostream & out, int offset) const {
    out << "ConstInt(" << value << ")";
}

ExpressionPtr Int::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return Expression::New<Int> (value, new_pos);
}

ExpressionPtr Int::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value <= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value >= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value != e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value < e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value > e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value == e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value && e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value || e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value + e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value + e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value + e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value + e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value - e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value - e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value - e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value - e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value * e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value * e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value * e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value * e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value / e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value / e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value / e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value / e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Int::interpretMOD (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return Expression::New<Int> (value % e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value % e->getChar (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}


ExpressionPtr Int::interpretUnaryMINUS () {
    return Expression::New<Int> (value * -1, NULL_POSITION);
}

// ####################################

Float::Float (float value, Position * pos) {
    this->pos = pos;
    this->value = value;
    this->type = new Type ("float");
}

Float::~Float () {}

float Float::getFloat () const { return value; }

void Float::print (ostream & out, int offset) const {
    out << "ConstFloat(" << std::to_string (this->value) << ")";
}

ExpressionPtr Float::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return Expression::New<Float> (value, new_pos);
}

ExpressionPtr Float::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value <= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value >= e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value != e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value < e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value > e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value == e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value && e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value || e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value + e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value + e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value + e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value + e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value - e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value - e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value - e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value - e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value * e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value * e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value * e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value * e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value / e->getFloat (), NULL_POSITION);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value / e->getInt (), NULL_POSITION);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value / e->getChar (), NULL_POSITION);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value / e->getBool (), NULL_POSITION);
    } else {
	throw TypeErrorException (shared_from_this (), e, pos);
    }
}

ExpressionPtr Float::interpretUnaryMINUS () {
    return Expression::New<Float> (value * -1, NULL_POSITION);
}

// ####################################

Array::Array (vector<ExpressionPtr> * array, Position * pos) {
    this->pos = pos;
    this->array = array;
    this->type = new Type ("array");
}

ExpressionPtr Array::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    vector<ExpressionPtr> * vec = new vector<ExpressionPtr> ();

    for (auto it : *(array)) {
	vec->push_back (it->clone ());
    }
    return Expression::New<Array> (vec, new_pos);
}

Array::Array () {}

Array::~Array () {
    if (array != NULL)
	delete array;
}

vector<ExpressionPtr> * Array::getArray () const { return array; }

void Array::print (ostream & out, int offset) const {
    out << "<array>[";
    if (array != NULL) {
	int i = 0;
	for (auto it : *array) {
	    it->print (out);
	    if (i < array->size () -1)
		out << ", ";
	    ++i;
	}
    }
    out << "]";
}

ExpressionPtr Array::interpretExpression () {
    for (auto & it : *array)
	it = it->interpretExpression ();
    
    return shared_from_this ();
}

ExpressionPtr Array::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    // if e is not an array, we add it at the end of the array
    if (e_type != TYPE::ARRAY && e_type != TYPE::STRING) {
	array->push_back (e->clone ());
    } else {
	vector<ExpressionPtr> * e_array = e->getArray ();
	for (auto it : *(e_array)) {
	    array->push_back (it->clone ());
	}
    }
    return shared_from_this ();
}

// ####################################

String::String (string str, Position * pos) {
    this->array = new vector<ExpressionPtr> ();
    for (int i = 0; i < str.size (); i++)
	this->array->push_back (Expression::New<Char> (str[i], new Position (pos->line, pos->column)));
    this->pos = pos;
    this->type = new Type ("string");
}

void String::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "\"";
    for (auto it : *array)
	out << it->getChar ();
    out << "\"";
}

// ####################################

Range::Range (ExpressionPtr begin, ExpressionPtr end, Position * pos) {
    this->pos = pos;
    this->begin = begin;
    this->end = end;
    this->type = new Type ("range");
}

ExpressionPtr Range::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return Expression::New<Range> (begin->clone (), end->clone (), new_pos);
}

Range::~Range () {
}

ExpressionPtr Range::getRangeBegin () const { return begin; }
ExpressionPtr Range::getRangeEnd () const { return end; }

void Range::print (ostream & out, int offset) const {
    out << "<range>[";
    begin->print (out);
    out << " .. ";
    end->print (out);
    out << "]";
}

ExpressionPtr Range::interpretExpression () {
    ExpressionPtr first = begin->interpretExpression ();
    ExpressionPtr second = end->interpretExpression ();
    if (first->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, first->getType (), first->pos);
    } else if (second->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, second->getType (), second->pos);
    }
    begin = first;
    end = second;
    return shared_from_this ();
}

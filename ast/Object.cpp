#include "Object.hpp"
#include "exceptions/SemanticException.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bool::Bool(bool value, Position * pos) : Expression (pos) {
    _type = new Type ("bool");
    this->value = value;
}

Bool::~Bool() {}

bool Bool::getBool () const { return value; }

void Bool::print (ostream & out, int offset) const {
    out << "ConstBool(" << (value ? "true" : "false") << ")";
}

ExpressionPtr Bool::clone () {
    Position * new_pos = new Position (_pos->line, _pos->column);
    return Expression::New<Bool> (value, new_pos);
}

ExpressionPtr Bool::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value <= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;
    
    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value >= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value != e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value < e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value > e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value == e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value && e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value || e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value + e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value + e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value + e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value + e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value - e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value - e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value - e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value - e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value * e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value * e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value * e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value * e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value / e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value / e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value / e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value / e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Bool::interpretMOD (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value / e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value / e->getChar (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}


ExpressionPtr Bool::interpretUnaryMINUS () {
    return Expression::New<Bool> (value * -1, NULL_POSITION_PTR);
}


// ####################################

Char::Char(char value, Position * pos) : Expression (pos) {
    _type = new Type ("char");
    this->value = value;
}

Char::~Char() {}

char Char::getChar () const { return value; }

void Char::print (ostream & out, int offset) const {
    out << "ConstChar(" << "'" << value << "'" << ")";
}

ExpressionPtr Char::clone () {
    Position * new_pos = new Position (_pos->line, _pos->column);
    return Expression::New<Char> (value, new_pos);
}

ExpressionPtr Char::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value <= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value >= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value != e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value < e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value > e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value == e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value && e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value || e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value + e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value + e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value + e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value + e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value - e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value - e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value - e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value - e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value * e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value * e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value * e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value * e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Char> ((float) value / e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Char> (value / e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value / e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Char> (value / e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Char::interpretMOD (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return Expression::New<Char> (value % e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Char> (value % e->getChar (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}


ExpressionPtr Char::interpretUnaryMINUS () {
    return Expression::New<Char> (value * -1, NULL_POSITION_PTR);
}

// ####################################

Int::Int(int v, Position * pos) : Expression (pos) {
    this->value = v;
    _type = new Type ("int");
}

Int::~Int() { }

int Int::getInt () const { return value; }

void Int::setInt (int v) { value = v; }

void Int::print (ostream & out, int offset) const {
    out << "ConstInt(" << value << ")";
}

ExpressionPtr Int::clone () {
    Position * new_pos = new Position (_pos->line, _pos->column);
    return Expression::New<Int> (value, new_pos);
}

ExpressionPtr Int::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value <= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value >= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value != e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value < e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value > e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value == e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value && e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> ((float) value || e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value + e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value + e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value + e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value + e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value - e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value - e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value - e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value - e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value * e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value * e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value * e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value * e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Int> ((float) value / e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Int> (value / e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value / e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Int> (value / e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Int::interpretMOD (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return Expression::New<Int> (value % e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Int> (value % e->getChar (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}


ExpressionPtr Int::interpretUnaryMINUS () {
    return Expression::New<Int> (value * -1, NULL_POSITION_PTR);
}

// ####################################

Float::Float (float value, Position * pos) : Expression (pos) {
    this->value = value;
    _type = new Type ("float");
}

Float::~Float () {}

float Float::getFloat () const { return value; }

void Float::print (ostream & out, int offset) const {
    out << "ConstFloat(" << std::to_string (this->value) << ")";
}

ExpressionPtr Float::clone () {
    Position * new_pos = new Position (_pos->line, _pos->column);
    return Expression::New<Float> (value, new_pos);
}

ExpressionPtr Float::interpretLE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value <= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value <= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value <= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value <= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretGE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value >= e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value >= e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value >= e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value >= e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretNE (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value != e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value != e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value != e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value != e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretLT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value < e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value < e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value < e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value < e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretGT (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value > e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value > e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value > e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value > e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretEQ (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value == e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value == e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value == e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value == e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretAND (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value && e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value && e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value && e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value && e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretOR (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Bool> (value || e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Bool> (value || e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Bool> (value || e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Bool> (value || e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretPLUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value + e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value + e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value + e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value + e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretMINUS (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value - e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value - e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value - e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value - e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretMUL (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value * e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value * e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value * e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value * e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretDIV (ExpressionPtr e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return Expression::New<Float> (value / e->getFloat (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::INT) {
	return Expression::New<Float> (value / e->getInt (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::CHAR) {
	return Expression::New<Float> (value / e->getChar (), NULL_POSITION_PTR);
    } else if (e_type == TYPE::BOOL) {
	return Expression::New<Float> (value / e->getBool (), NULL_POSITION_PTR);
    } else {
	throw TypeErrorException (shared_from_this (), e, _pos);
    }
}

ExpressionPtr Float::interpretUnaryMINUS () {
    return Expression::New<Float> (value * -1, NULL_POSITION_PTR);
}

// ####################################

Array::Array (vector<ExpressionPtr> * array, Position * pos) : Expression (pos) {
    this->array = array;
    _type = new Type ("array");
}

ExpressionPtr Array::clone () {
    Position * new_pos = new Position (_pos->line, _pos->column);
    vector<ExpressionPtr> * vec = new vector<ExpressionPtr> ();

    for (auto it : *(array)) {
	vec->push_back (it->clone ());
    }
    return Expression::New<Array> (vec, new_pos);
}

Array::Array (Position * pos) : Expression (pos) {}

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

String::String (string str, Position * pos) : Array (pos) {
    this->array = new vector<ExpressionPtr> ();
    for (int i = 0; i < str.size (); i++)
	this->array->push_back (Expression::New<Char> (str[i], new Position (_pos->line, _pos->column)));
    _type = new Type ("string");
}

void String::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "\"";
    for (auto it : *array)
	out << it->getChar ();
    out << "\"";
}

// ####################################

Range::Range (ExpressionPtr begin, ExpressionPtr end, Position * pos) : Expression (pos) {
    this->begin = begin;
    this->end = end;
    _type = new Type ("range");
}

ExpressionPtr Range::clone () {
    Position * new_pos = new Position (_pos->line, _pos->column);
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
	throw TypeErrorException (&t, first->getType (), first->getPos ());
    } else if (second->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, second->getType (), second->getPos ());
    }
    begin = first;
    end = second;
    return shared_from_this ();
}

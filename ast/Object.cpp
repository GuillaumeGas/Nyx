#include "Object.hpp"
#include "exceptions/SemanticException.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

AbstractObject::AbstractObject () {
    nb_ref = 0;
}

AbstractObject::~AbstractObject () {
    if (type) {
	delete type;
    }
}

int AbstractObject::getNbRef () const { return nb_ref; }
void AbstractObject::setNbRef (const int nb) { nb_ref = nb; }

Type * AbstractObject::getType () const { return type; }
AbstractObject * AbstractObject::getPtr () { return this; }

bool AbstractObject::getBool () const { throw -1; }
int AbstractObject::getInt () const { throw -1; }
char AbstractObject::getChar () const { throw -1; }
float AbstractObject::getFloat () const { throw -1; }
vector<Expression*> * AbstractObject::getArray () const { throw -1; }
AbstractObject * AbstractObject::getRangeStart () const { throw -1; }
AbstractObject * AbstractObject::getRangeEnd () const { throw -1; }
// Object * AbstractObject::getObject () const { throw -1; }


AbstractObject * AbstractObject::interpretASSIGN (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretLE (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretGE (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretNE (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretPLUSEQ (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretMINUSEQ (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretMULEQ (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretDIVEQ (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretMODEQ (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretLT (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretGT (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretEQ (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretAND (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretOR (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretPLUS (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretMINUS (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretMUL (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretDIV (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretMOD (AbstractObject * e) { throw TypeErrorException (this, e, pos); }
AbstractObject * AbstractObject::interpretPOINT (AbstractObject * e) { throw TypeErrorException (this, e, pos); }

AbstractObject * AbstractObject::interpretUnaryMINUS () { throw SemanticErrorException ("Bad operand type for unary '-' : " + type->toString (), pos); }

// #########################################""

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

Expression * Bool::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Bool (value, new_pos);
}

AbstractObject * Bool::interpretExpression () { 
    symbol::GarbageCollector::getInstance ()->addObject (this);
    return this;
}

AbstractObject * Bool::interpretLE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Bool (value <= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Bool (value <= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Bool (value <= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretGE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value >= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value >= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value >= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretNE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value != e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value != e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value != e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretLT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value < e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value < e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value < e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretGT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value > e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value > e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value > e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretEQ (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value == e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value == e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value == e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretAND (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value && e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value && e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value && e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretOR (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value || e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value || e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value || e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Bool::interpretPLUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value + e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value + e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value + e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Bool::interpretMINUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value - e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value - e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value - e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Bool::interpretMUL (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value * e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value * e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value * e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Bool::interpretDIV (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	new Bool (value / e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	new Bool (value / e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value / e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Bool::interpretMOD (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	new Bool (value % e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	new Bool (value % e->getChar (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}


AbstractObject * Bool::interpretUnaryMINUS () {
    new Bool (value * -1, NULL);
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

Expression * Char::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Char (value, new_pos);
}

AbstractObject * Char::interpretExpression () { 
    symbol::GarbageCollector::getInstance ()->addObject (this);
    return this;
}

AbstractObject * Char::interpretLE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value <= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value <= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value <= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretGE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value >= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value >= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value >= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretNE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value != e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value != e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value != e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretLT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value < e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value < e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value < e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretGT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value > e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value > e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value > e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretEQ (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value == e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value == e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value == e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretAND (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value && e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value && e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value && e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretOR (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value || e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value || e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value || e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Char::interpretPLUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value + e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value + e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value + e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Char::interpretMINUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value - e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value - e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value - e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Char::interpretMUL (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char ((float) value * e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value * e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value * e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Char::interpretDIV (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Char (value / e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Char (value / e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value / e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Char::interpretMOD (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return new Char (value % e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Char (value % e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Char (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}


AbstractObject * Char::interpretUnaryMINUS () {
    return new Char (value * -1, NULL);
}

// ####################################

Int::Int(int v, Position * pos) {
    this->pos = pos;
    this->value = v;
    this->type = new Type ("int");
}

Int::~Int() {}

int Int::getInt () const { return value; }

void Int::print (ostream & out, int offset) const {
    out << "ConstInt(" << value << ")";
}

Expression * Int::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Int (value, new_pos);
}

AbstractObject * Int::interpretExpression () { 
    symbol::GarbageCollector::getInstance ()->addObject (this);
    return this;
}

AbstractObject * Int::interpretLE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Bool ((float) value <= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Bool (value <= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Bool (value <= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Bool (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretGE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value >= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value >= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value >= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretNE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value != e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value != e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value != e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretLT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value < e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value < e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value < e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretGT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value > e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value > e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value > e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretEQ (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value == e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value == e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value == e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretAND (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value && e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value && e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value && e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretOR (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value || e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value || e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value || e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Int::interpretPLUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value + e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value + e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value + e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Int::interpretMINUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value - e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value - e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value - e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Int::interpretMUL (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value * e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int (value * e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value * e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Int::interpretDIV (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Int ((float) value / e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Int ((float) value / e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int ((float) value / e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Int (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Int::interpretMOD (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::INT) {
	return new Int (value % e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Int (value % e->getChar (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}


AbstractObject * Int::interpretUnaryMINUS () {
    return new Int (value * -1, NULL);
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

Expression * Float::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Float (value, new_pos);
}

AbstractObject * Float::interpretExpression () { 
    symbol::GarbageCollector::getInstance ()->addObject (this);
    return this;
}

AbstractObject * Float::interpretLE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float ( value <= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value <= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value <= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretGE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value >= e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value >= e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value >= e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretNE (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value != e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value != e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value != e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretLT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value < e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value < e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value < e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretGT (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value > e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value > e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value > e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretEQ (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value == e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value == e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value == e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretAND (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value && e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value && e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value && e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretOR (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value || e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value || e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value || e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

AbstractObject * Float::interpretPLUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value + e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value + e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value + e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Float::interpretMINUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value - e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value - e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value - e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Float::interpretMUL (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value * e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value * e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value * e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Float::interpretDIV (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	return new Float (value / e->getFloat (), NULL);
    } else if (e_type == TYPE::INT) {
	return new Float (value / e->getInt (), NULL);
    } else if (e_type == TYPE::CHAR) {
	return new Float (value / e->getChar (), NULL);
    } else if (e_type == TYPE::BOOL) {
	return new Float (value <= e->getBool (), NULL);
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

AbstractObject * Float::interpretUnaryMINUS () {
    return new Float (value * -1, NULL);
}

// ####################################

Array::Array (vector<Expression*> * array, Position * pos) {
    this->pos = pos;
    this->array = array;
    this->type = new Type ("array");
}

Expression * Array::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    vector<Expression*> * vec = new vector<Expression*> ();

    for (auto it : *(array)) {
	AbstractObject * obj = (AbstractObject *)it;
	vec->push_back (obj->clone ());
    }
    return new Array (vec, new_pos);
}

Array::Array () {}

Array::~Array () {
    if (array != NULL) {
	for (auto it : *array) {
	    if (it)
		delete it;
	}
	delete array;
    }
}

vector<Expression*> * Array::getArray () const { return array; }

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

AbstractObject * Array::interpretExpression () {
    for (auto & it : *array)
	it = it->interpretExpression ();
    symbol::GarbageCollector::getInstance ()->addObject (this);
    return this;
}

AbstractObject * Array::interpretPLUS (AbstractObject * e) {
    TYPE e_type = e->getType ()->value;

    // if e is not an array, we add it at the end of the array
    if (e_type != TYPE::ARRAY && e_type != TYPE::STRING) {
	array->push_back (e->clone ());
    } else {
	vector<Expression*> * e_array = e->getArray ();
	for (auto it : *(e_array)) {
	    AbstractObject * obj = (AbstractObject*) it;
	    array->push_back (obj->clone ());
	}
    }
    return this;
}

// ####################################

String::String (string str, Position * pos) {
    this->array = new vector<Expression*> ();
    for (int i = 0; i < str.size (); i++)
	this->array->push_back (new Char (str[i], new Position (pos->line, pos->column)));
    this->pos = pos;
    this->type = new Type ("string");
}

void String::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "\"";
    for (auto it : *array)
	out << ((Char*)it)->getChar ();
    out << "\"";
}

AbstractObject * String::interpretExpression () {
    symbol::GarbageCollector::getInstance ()->addObject (this);
    return this;
}

// ####################################

Range::Range (Expression * start, Expression * end, Position * pos) {
    this->pos = pos;
    this->start = start;
    this->end = end;
    this->type = new Type ("range");
}

Expression * Range::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Range (((AbstractObject*)start)->clone (), ((AbstractObject*)end)->clone (), new_pos);
}

Range::~Range () {
    if (start)
	delete start;
    if (end)
	delete end;
}

AbstractObject * Range::getRangeStart () const { return (AbstractObject*) start; }
AbstractObject * Range::getRangeEnd () const { return (AbstractObject*) end; }

void Range::print (ostream & out, int offset) const {
    out << "<range>[";
    start->print (out);
    out << " .. ";
    end->print (out);
    out << "]";
}

AbstractObject * Range::interpretExpression () {
    symbol::GarbageCollector::getInstance ()->addObject (this);
    AbstractObject * first = (AbstractObject*) start->interpretExpression ();
    AbstractObject * second = (AbstractObject*) end->interpretExpression ();
    if (first->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, first->getType (), first->pos);
    } else if (second->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, second->getType (), second->pos);
    }
    return this;
}

#include "Const.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bool::Bool(bool value, Position * pos) {
    this->value = new Value (value);
    this->pos = pos;
}

Bool::~Bool() {}

void Bool::print (ostream & out, int offset) const {
    out << (value->getBool () ? "true" : "false");
}

// ####################################

Char::Char(char value, Position * pos) {
    this->value = new Value (value);
    this->pos = pos;
}

Char::~Char() {}

// Expression * Char::interpretExpression () { return this; }

// Expression * Char::interpretPlus (Expression * e) {
//     if (e->getType ()->value != TYPE::CHAR)
// 	throw TypeErrorException (this, e, pos);
//     value->set (value->getChar () + e->value->getChar ());
//     return this;
// }

void Char::print (ostream & out, int offset) const {
    out << "'" << value->getChar () << "'";
}

// ####################################

Int::Int(int v, Position * pos) {
    this->value = new Value (v);
    this->pos = pos;
}

Int::~Int() {}

Value Int::interpretExpression () { return *value; }

Value Int::interpretPlus (Expression * e) {
    if (e->getValue ()->getType ()->value != TYPE::INT)
	throw TypeErrorException (this, e, pos);
    value->set (value->getInt () + e->getValue ()->getInt ());
    return *value;
}

Value Int::interpretMinus (Expression * e) {
    if (e->getValue ()->getType ()->value != TYPE::INT)
	throw TypeErrorException (this, e, pos);
    value->set (value->getInt () - e->getValue ()->getInt ());
    return *value;
}

void Int::print (ostream & out, int offset) const {
    out << value->getInt ();
}

// ####################################

Float::Float (float value, Position * pos) {
    this->value = new Value (value);
    this->pos = pos;
}

Float::~Float () {}

void Float::print (ostream & out, int offset) const {
    out << std::to_string (this->value->getFloat ());
}

// ####################################

String::String (string * value, Position * pos) {
    this->value = new Value ((void*)value);
    this->pos = pos;
}

String::~String () {}

void String::print (ostream & out, int offset) const {
    out << "\"" << *((string*)(value->getPtr ())) << "\"";
}

// Expression * String::interpretExpression () {
//     return this;
// }

// ####################################

Array::Array (vector<Expression*> * array, Position * pos) {
    this->pos = pos;
    this->array = array;
}

Array::~Array () {
    if (array != NULL) {
	for (auto it : *array) {
	    if (it)
		delete it;
	}
    }
}

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

// Expression * Array::interpretExpression () {
//     for (auto it : *array) {
// 	it->interpretExpression ();
//     }
//     return this;
// }

// ####################################

Range::Range (Expression * start, Expression * end, Position * pos) {
    this->pos = pos;
    this->start = start;
    this->end = end;
}

Range::~Range () {
    if (start)
	delete start;
    if (end)
	delete end;
}

void Range::print (ostream & out, int offset) const {
    out << "<range>[";
    start->print (out);
    out << " .. ";
    end->print (out);
    out << "]";
}

// Expression * Range::interpretExpression () {
//     start = start->interpretExpression ();
//     end = end->interpretExpression ();
//     if (start->getType ()->value != TYPE::INT) {
// 	Type t ("int");
// 	throw TypeErrorException (&t, start->getType (), start->pos);
//     } else if (end->getType ()->value != TYPE::INT) {
// 	Type t ("int");
// 	throw TypeErrorException (&t, end->getType (), end->pos);
//     }
//     return this;
// }

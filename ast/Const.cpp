#include "Const.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bool::Bool(bool value, Position * pos) {
    this->value->Bool = value;
    this->pos = pos;
    this->type = new Type("bool", true);
}

Bool::~Bool() {}

void Bool::print (ostream & out, int offset) const {
    out << "ConstBool(" << (value ? "true" : "false") << ")";
}

Char::Char(char value, Position * pos) {
    this->value->Char = value;
    this->pos = pos;
    this->type = new Type("char", true);
}

Char::~Char() {}

Expression * Char::interpretExpression () { return this; }

Expression * Char::interpretPlus (Expression * e) {
    if (e->getType ()->value != TYPE::CHAR)
	throw TypeErrorException (this, e, pos);
    value->Int = value->Char + e->value->Char;
    return this;
}

void Char::print (ostream & out, int offset) const {
    out << "ConstChar(" << "'" << value->Char << "'" << ")";
}

Int::Int(int v, Position * pos) {
    this->value->Int = v;
    this->pos = pos;
    this->type = new Type("int", true);
}

Int::~Int() {}

Expression * Int::interpretExpression () { return this; }

Expression * Int::interpretPLUS (Expression * e) {
    if (e->getType ()->value != TYPE::INT)
	throw TypeErrorException (this, e, pos);
    value->Int = value->Int + e->getValue ()->Int;
    return this;
}

Expression * Int::interpretMINUS (Expression * e) {
    if (e->getType ()->value != TYPE::INT)
	throw TypeErrorException (this, e, pos);
    value->Int = value->Int - e->getValue ()->Int;
    return this;
}

void Int::print (ostream & out, int offset) const {
    out << "ConstInt(" << value->Int << ")";
}

Expression * Int::interpretUnaryMINUS () {
    value->Int *= -1;
    return this;
}

Float::Float (float value, Position * pos) {
    this->value->Float = value;
    this->pos = pos;
    this->type = new Type ("float", true);
}

Expression * Float::interpretExpression () { return this; }

Float::~Float () {}

void Float::print (ostream & out, int offset) const {
    out << "ConstFloat(" << std::to_string (this->value->Float) << ")";
}

Array::Array (vector<Expression*> * array, Position * pos) {
    this->pos = pos;
    this->type = new Type ("array", false);
    this->array = array;
}

Array::Array () {}

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
	for (int i = 0; i < array->size (); i++) {
	    (*array)[i]->print (out);
	    if (i < array->size()-1)
		out << ", ";
	}
    }
    out << "]";
}

Expression * Array::interpretExpression () {
    for (auto it : *array) {
	it->interpretExpression ();
    }
    return this;
}

String::String (string str, Position * pos) {
    this->array = new vector<Expression*> ();
    for (int i = 0; i < str.size (); i++)
	this->array->push_back (new Char (str[i], pos));
    this->pos = pos;
    this->type = new Type ("string", false);
}

String::~String () {
    if (array) {
	for (auto it : *array) {
	    if (it)
		delete it;
	}
	delete array;
    }
}

void String::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "\"";
    for (auto it : *array)
	out << it->getValue ()->Char;
    out << "\"";
}

Expression * String::interpretExpression () {
    return this;
}

Range::Range (Expression * start, Expression * end, Position * pos) {
    this->pos = pos;
    this->start = start;
    this->end = end;
    this->type = new Type("range", true);
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

Expression * Range::interpretExpression () {
    start = start->interpretExpression ();
    end = end->interpretExpression ();
    if (start->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, start->getType (), start->pos);
    } else if (end->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, end->getType (), end->pos);
    }
    return this;
}

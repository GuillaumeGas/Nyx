
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
    out << (value ? "true" : "false");
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
    out << "'" << value->Char << "'";
}

Int::Int(int v, Position * pos) {
    this->value->Int = v;
    this->pos = pos;
    this->type = new Type("int", true);
}

Int::~Int() {}

Expression * Int::interpretExpression () { return this; }

Expression * Int::interpretPlus (Expression * e) {
    if (e->getType ()->value != TYPE::INT)
	throw TypeErrorException (this, e, pos);
    value->Int = value->Int + e->value->Int;
    return this;
}

void Int::print (ostream & out, int offset) const {
    out << value->Int;
}

Float::Float (float value, Position * pos) {
    this->value->Float = value;
    this->pos = pos;
    this->type = new Type ("float", true);
}

Float::~Float () {}

void Float::print (ostream & out, int offset) const {
    out << std::to_string (this->value->Float);
}

String::String (string * value, Position * pos) {
    this->value->Str = value;
    this->pos = pos;
    this->type = new Type ("string", true);
}

String::~String () {
    if (this->value->Str)
	delete this->value->Str;
}

void String::print (ostream & out, int offset) const {
    out << "\"" << *(value->Str) << "\"";
}

Expression * String::interpretExpression () {
    return this;
}

Array::Array (vector<Expression*> * array, Position * pos) {
    this->pos = pos;
    this->type = new Type ("array", false);
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
    out << "[";
    if (array != NULL) {
	for (int i = 0; i < array->size (); i++) {
	    (*array)[i]->print (out);
	    if (i < array->size()-1)
		out << ", ";
	}
    }
    out << "]";
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
    out << "[";
    start->print (out);
    out << " .. ";
    end->print (out);
    out << "]";
}

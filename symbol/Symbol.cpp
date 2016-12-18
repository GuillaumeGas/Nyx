#include "Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Symbol::Symbol (string & name, ast::Type * type) : name (name) {
    this->value = new ast::Value ();
    this->type = type;
}

Symbol::Symbol (string & name, int value) : name (name) {
    this->value = new ast::Value ();
    this->type = new ast::Type ("int");
    this->value->Int = value;
}

Symbol::Symbol (string & name, float value) : name (name) {
    this->value = new ast::Value ();
    this->type = new ast::Type ("float");
    this->value->Float = value;
}

Symbol::Symbol (string & name, bool value) : name (name) {
    this->value = new ast::Value ();
    this->type = new ast::Type ("bool");
    this->value->Bool = value;
}

Symbol::Symbol (string & name, char value) : name (name) {
    this->value = new ast::Value ();
    this->type = new ast::Type ("char");
    this->value->Char = value;
}

Symbol::Symbol (string & name, string * value) : name (name) {
    this->value = new ast::Value ();
    this->type = new ast::Type ("string");
    this->value->Str = value;
}

Symbol::~Symbol() {
    if (type)
	delete type;
    if (value)
	delete value;
}

void Symbol::setValue (int value) {
    this->value->Int = value;
}
void Symbol::setValue (float value) {
    this->value->Float = value;
}
void Symbol::setValue (bool value) {
    this->value->Bool = value;
}
void Symbol::setValue(char value) {
    this->value->Char = value;
}
void Symbol::setValue (string * value) {
    if (this->value->Str)
	delete this->value->Str;
    this->value->Str = value;
}

ast::Type * Symbol::getType() const {
    return type;
}

ast::Value * Symbol::getValue () const {
    return value;
}

string Symbol::toString() const {
    stringstream ss;
    ss << "[" << name << ", ";
    switch (type->value) {
    case ast::TYPE::INT:
	ss << value->Int;
	break;
    case ast::TYPE::FLOAT:
	ss << value->Float;
	break;
    case ast::TYPE::BOOL:
	ss << value->Bool;
	break;
    case ast::TYPE::CHAR:
	ss << value->Char;
	break;
    case ast::TYPE::STRING:
	ss << (*value->Str);
	break;
    default:
	cout << "Error toString" << endl;
    }
    ss << "]" << endl;
    return ss.str ();
}

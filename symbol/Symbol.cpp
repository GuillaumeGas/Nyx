#include "Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Symbol::Symbol (string & name) : name (name) {
    this->value = new ast::Value ();
}

Symbol::Symbol (string & name, int value) : name (name) {
    this->value = new ast::Value (value);
    this->value->set (value);
}

Symbol::Symbol (string & name, float value) : name (name) {
    this->value = new ast::Value (value);
    this->value->set (value);
}

Symbol::Symbol (string & name, bool value) : name (name) {
    this->value = new ast::Value (value);
    this->value->set (value);
}

Symbol::Symbol (string & name, char value) : name (name) {
    this->value = new ast::Value (value);
    this->value->set (value);
}

Symbol::Symbol (string & name, ast::Expression * value) : name (name) {
    this->value = new ast::Value (value);
    this->value->set (value);
}

Symbol::~Symbol() {
    if (type)
	delete type;
    if (value)
	delete value;
}

void Symbol::setValue (int value) {
    this->value->set (value);
    ast::Type t ("int");
    this->setType (&t);
}
void Symbol::setValue (float value) {
    this->value->set (value);
    ast::Type t ("float");
    this->setType (&t);
}
void Symbol::setValue (bool value) {
    this->value->set (value);
    ast::Type t ("bool");
    this->setType (&t);
}
void Symbol::setValue(char value) {
    this->value->set (value);
    ast::Type t ("char");
    this->setType (&t);
}
// void Symbol::setValue (string * value) {
//     if (this->value->Str)
// 	delete this->value->Str;
//     this->value->Str = new string (*value);
// }

void Symbol::setType (ast::Type * type) {
    if (!this->type)
	this->type = new ast::Type (*type);
    this->type->value = type->value;
    this->type->name = type->name;
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
	ss << value->getInt ();
	break;
    case ast::TYPE::FLOAT:
	ss << value->getFloat ();
	break;
    case ast::TYPE::BOOL:
	ss << value->getBool ();
	break;
    case ast::TYPE::CHAR:
	ss << value->getChar ();
	break;
    case ast::TYPE::VOID:
	ss << "void";
	break;
    default:
	cout << "Error toString" << endl;
    }
    ss << "]" << endl;
    return ss.str ();
}

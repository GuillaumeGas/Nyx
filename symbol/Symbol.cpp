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

void Symbol::setValue (ast::Expression * value) {
    this->value->set (value);
    ast::Type t("ptr", false);
    this->setType (&t);
}
void Symbol::setValue (ast::Expression * value, const string type) {
    this->value->set (value, type);
    ast::Type t(type, false);
    this->setType (&t);
}

void Symbol::setType (ast::Type * type) {
    if (!this->type)
	this->type = new ast::Type (*type);
    this->type->value = type->value;
    this->type->name = type->name;
}

ast::Value * Symbol::getValue () const {
    return value;
}

string Symbol::toString() const {
    stringstream ss;
    ss << "[" << name << ", ";

    switch (value->getType ()->value) {
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
    case ast::TYPE::ARRAY:
    case ast::TYPE::STRING:
    case ast::TYPE::RANGE:
	ss << "ptr";
	break;
    default:
	cout << "Unknown type" << endl;
    }
    ss << "] " << value->getType ()->toString () << endl;
    return ss.str ();
}

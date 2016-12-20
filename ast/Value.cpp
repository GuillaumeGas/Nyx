#include "Value.hpp"

using namespace nyx;
using namespace ast;

Value::Value (int val) {
    _init ();
    _value.Int = val;
    _type = new Type ("int");
}

Value::Value (char val) {
    _init ();
    _value.Char = val;
    _type = new Type ("char");
}

Value::Value (float val) {
    _init ();
    _value.Float = val;
    _type = new Type ("float");
}

Value::Value (double val) {
    _init ();
    _value.Double = val;
    _type = new Type ("double");
}

Value::Value (bool val) {
    _init ();
    _value.Bool = val;
    _type = new Type ("bool");
}

// Value::Value (void * ptr) {
//     _init ();
//     _value.Ptr = ptr;
//     _type = new Type ("ptr", false);
// }

Value::~Value () {
    // if (_type->value == TYPE::PTR) {
    // 	if (_value.Ptr)
    // 	    delete _value.Ptr;
    // }
    delete _type;
}

int Value::getInt () const { return _value.Int; }
char Value::getChar () const { return _value.Char; }
float Value::getFloat () const { return _value.Float; }
double Value::getDouble () const { return _value.Double; }
bool Value::getBool () const { return _value.Bool; }
void * Value::getPtr () const { return _value.Ptr; }

void Value::set (int val) {
    _checkPtr ();
    type->setType ("int");
    _value.Int = val;
}

void Value::set (char val) {
    _checkPtr ();
    type->setType ("char");
    _value.Char = val;
}

void Value::set (float val) {
    _checkPtr ();
    type->setType ("float");
    _value.Float = val;
}

void Value::set (double val) {
    _checkPtr ();
    type->setType ("double");
    _value.Double = val;
}

void Value::set (bool val) {
    _checkPtr ();
    type->setType ("bool");
    _value.Bool = val;
}

void Value::set (void * val) {
    _checkPtr ();
    type->setType ("ptr");
    _value.Ptr = val;
}

string Value::toString () const {
    string res = "<" + _type->toString() + ">(";
    switch (_type->value) {
    case TYPE::INT:
	res += to_string (_value.Int);
	break;
    case TYPE::FLOAT:
	res += to_string (_value.Float);
	break;
    case TYPE::DOUBLE:
	res += to_string (_value.Double);
	break;
    case TYPE::BOOL:
	res += to_string (_value.Bool);
	break;
    case TYPE::CHAR:
	res += _value.Char;
	break;
    case TYPE::PTR:
	res += ((Expression*)(_value.Ptr))->toString ();
	break;
    default:
	res += "ERROR Value : unknown type";
    }
    res += ")";
}

void Value::_init () {
    _value.Ptr = NULL;
}

void Value::_checkPtr () {
    if (_type->value == TYPE::PTR)
	delete _value.Ptr;
}

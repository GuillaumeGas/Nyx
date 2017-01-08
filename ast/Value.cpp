#include "Value.hpp"
#include "Expression.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Value::Value () {
    _type = new Type ("void");
}

Value::Value (const Value & v) {
    _type = new Type (*(v._type));
    _value = v._value;
}

Value::Value (int val) {
    _value.Int = val;
    _type = new Type ("int");
}

Value::Value (char val) {
    _value.Char = val;
    _type = new Type ("char");
}

Value::Value (float val) {
    _value.Float = val;
    _type = new Type ("float");
}

Value::Value (bool val) {
    _value.Bool = val;
    _type = new Type ("bool");
}

Value::Value (Expression * ptr) {
    _value.Ptr = ptr;
    _type = new Type ("ptr", false);
}

Value::Value (Expression * ptr, const string type) {
    _value.Ptr = ptr;
    _type = new Type (type, false);
}

Value::~Value () {
    if (_type)
    	delete _type;
}

int Value::getInt () const { return _value.Int; }
char Value::getChar () const { return _value.Char; }
float Value::getFloat () const { return _value.Float; }
bool Value::getBool () const { return _value.Bool; }
Expression * Value::getPtr () const { return _value.Ptr; }

Type * Value::getType () const { return _type; }

void Value::set (int val) {
    _type->setType ("int");
    _value.Int = val;
}

void Value::set (char val) {
    _type->setType ("char");
    _value.Char = val;
}

void Value::set (float val) {
    _type->setType ("float");
    _value.Float = val;
}

void Value::set (bool val) {
    _type->setType ("bool");
    _value.Bool = val;
}

void Value::set (Expression * val) {
    _type->setType ("ptr");
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
    case TYPE::BOOL:
	res += to_string (_value.Bool);
	break;
    case TYPE::CHAR:
	res += _value.Char;
	break;
    case TYPE::PTR:
	res += "ptr";
	// res += ((Expression*)(_value.Ptr))->toString ();
	break;
    default:
	res += "ERROR Value : unknown type";
    }
    res += ")";
}

#include "Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Symbol::Symbol (string & name) {
    _name = name;
    _is_def = false;
}

Symbol::Symbol (string & name, ast::AbstractObject * ptr) {
    _name = name;
    _is_def = true;
}

Symbol::~Symbol() {}

ast::AbstractObject * Symbol::getValue () const {
    return _ptr;
}

string Symbol::getName () const {
    return _name;
}

void Symbol::setValue (ast::AbstractObject * v) {
    _ptr = v;
    _is_def = true;
}

bool Symbol::isDef () const {
    return _is_def;
}

string Symbol::toString() const {
    stringstream ss;
    ss << "[" << _name << ", ";

    if (_is_def) {
	switch (_ptr->getType ()->value) {
	case ast::TYPE::INT:
	    ss << _ptr->getInt ();
	    break;
	case ast::TYPE::FLOAT:
	    ss << _ptr->getFloat ();
	    break;
	case ast::TYPE::BOOL:
	    ss << _ptr->getBool ();
	    break;
	case ast::TYPE::CHAR:
	    ss << _ptr->getChar ();
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
	ss << "] " << _ptr->getType ()->toString () << endl;
    } else {
	ss << "undef" << "]";
    }
    return ss.str ();
}

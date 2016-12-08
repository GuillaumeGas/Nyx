#include "Type.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Type::Type(string name, bool is_basic) : name(name), is_basic(is_basic) {
    type = getType();
}

Type::~Type() {  }

string Type::toString() const {
    return name;
}

bool Type::isBasic () const {
    return is_basic;
}

TYPE Type::getType() const {
    if (name == "int") {
	return TYPE::INT;
    } else if (name == "char") {
	return TYPE::CHAR;
    } else if (name == "float") {
	return TYPE::FLOAT;
    } else if (name == "string") {
	return TYPE::STRING;
    } else if (name == "array") {
	return TYPE::ARRAY;
    } else {
	return TYPE::ERR;
    }
}

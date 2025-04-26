#include "Type.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Type::Type(const Type& type) : name(type.name), is_basic(type.is_basic) {
    value = getValue();
}

Type::Type(string name) : name(name) {
    value = getValue();
    is_basic = value != TYPE::STRUCT;
}

Type::Type(string name, bool is_basic) : name(name), is_basic(is_basic) {
    value = getValue();
}

Type::~Type() {  }

void Type::setType(string name, bool is_basic) {
    this->name = name;
    this->value = getValue();
    this->is_basic = is_basic;
}

void Type::setBasic(bool val) {
    this->is_basic = val;
}

string Type::toString() const {
    return name;
}

bool Type::isBasic() const {
    return is_basic;
}

TYPE Type::getValue() const {
    if (name == "int") {
        return TYPE::INT;
    }
    else if (name == "char") {
        return TYPE::CHAR;
    }
    else if (name == "float") {
        return TYPE::FLOAT;
    }
    else if (name == "bool") {
        return TYPE::BOOL;
    }
    else if (name == "string") {
        return TYPE::STRING;
    }
    else if (name == "array") {
        return TYPE::ARRAY;
    }
    else if (name == "range") {
        return TYPE::RANGE;
    }
    else if (name == "void") {
        return TYPE::_VOID;
    }
    else {
        return TYPE::STRUCT;
    }
}

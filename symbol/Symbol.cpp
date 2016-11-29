#include "Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Symbol::Symbol(string name, ast::Type * type) : name(name) {
    if (type->isBasic()) {
	ast::TYPE t = type->getType();
	if (t == ast::TYPE::INT) {
	    symbol_value = new SymbolIntValue(type, 0);
	} else if (t == ast::TYPE::CHAR) {
	    char c = -1;
	    symbol_value = new SymbolCharValue(type, c);
	} else {
	    cout << "[Error] Unknown type.";
	    exit(-1);
	}
    } else {
	cout << "[Error] Unknown type.";
	exit(-1);
    }
}
Symbol::Symbol(string name, ast::Type * type, int value) : name(name) {
    symbol_value = new SymbolIntValue(type, value);
}
Symbol::Symbol(string name, ast::Type * type, char value) : name(name) {
    symbol_value = new SymbolCharValue(type, value);
}
Symbol::Symbol(string name, ast::Type * type, string value) : name(name) {
    symbol_value = new SymbolStringValue(type, value);
}

Symbol::~Symbol() {
    if (symbol_value)
	delete symbol_value;
}

void Symbol::setValue(int value) {
    SymbolIntValue * s = (SymbolIntValue * ) symbol_value;
    s->value = value;
}
void Symbol::setValue(char value) {
    SymbolCharValue * s = (SymbolCharValue * ) symbol_value;
    s->value = value;
}
void Symbol::setValue(string value) {
    SymbolStringValue * s = (SymbolStringValue * ) symbol_value;
    s->value = value;
}

ast::Type * Symbol::getType() const {
    return symbol_value->type;
}

string Symbol::toString() const {
    return "[" + name + ", " + symbol_value->toString() + "]";
}

SymbolIntValue::SymbolIntValue(ast::Type * type, int val) : value(val) {
    this->type = type;
}

string SymbolIntValue::toString() const {
    return "(" + type->toString() + ") " +  std::to_string(value);
}

SymbolCharValue::SymbolCharValue(ast::Type * type, char val) : value(val) {
    this->type = type;
}

string SymbolCharValue::toString() const {
    return "(" + type->toString() + ") " +  std::to_string(value);
}

SymbolStringValue::SymbolStringValue(ast::Type * type, string val) : value(val) {
    this->type = type;
}

string SymbolStringValue::toString() const {
    return "(" + type->toString() + ") " +  value;
}




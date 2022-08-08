#include "Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Symbol::Symbol(string name, Position & pos) {
    _name = name;
    _is_def = false;
    _is_const = false;
    _used_at_least_once = false;
    _pos = pos;
}

Symbol::Symbol(string name, ast::ExpressionPtr ptr) {
    _name = name;
    _is_def = true;
    _is_const = false;
    _ptr = ptr;
    _used_at_least_once = false;
    _pos = *(ptr->getPos());
}

Symbol::~Symbol() {}

ast::ExpressionPtr Symbol::getValue() {
    return _ptr;
}

string Symbol::getName() const {
    return _name;
}

const Position& Symbol::getPos() const {
    return _pos;
}

void Symbol::setValue(ast::ExpressionPtr v) {
    if (!_is_const) {
        _ptr = v;
        _is_def = true;
    }
    else {
        cout << "[!] Cannot set a const var !" << endl;
        throw - 1;
    }
}

void Symbol::setConst(bool is_const) {
    _is_const = is_const;
}

bool Symbol::isDef() const {
    return _is_def;
}

string Symbol::toString() const {
    stringstream ss;
    ss << "[" << _name << ", ";

    if (_is_def) {
        switch (_ptr->getType()->value) {
        case ast::TYPE::INT:
            ss << _ptr->getInt();
            break;
        case ast::TYPE::FLOAT:
            ss << _ptr->getFloat();
            break;
        case ast::TYPE::BOOL:
            ss << _ptr->getBool();
            break;
        case ast::TYPE::CHAR:
            ss << _ptr->getChar();
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
        ss << "] " << _ptr->getType()->toString() << endl;
    }
    else {
        ss << "undef" << "]";
    }
    return ss.str();
}

ConstSymbol::ConstSymbol(string name, ast::ExpressionPtr ptr) : Symbol(name, ptr) {
    _is_const = true;
}

ConstSymbol::ConstSymbol(string name, Position& pos) : Symbol(name, pos) {
    _is_const = true;
}

FunSymbol::FunSymbol(string name, ast::FunctionPtr ptr) {
    _name = name;
    _ptr = ptr;
}

string FunSymbol::getName() const {
    return _name;
}

ast::FunctionPtr FunSymbol::getPtr() const {
    return _ptr;
}

string FunSymbol::toString() const {
    return _name;
}

bool Symbol::isUsed() const
{
    return _used_at_least_once;
}

void Symbol::isUsed(const bool used) {
    _used_at_least_once = used;
}

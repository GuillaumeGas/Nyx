#include "Scope.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

Scope::Scope(Scope * parent) {
    _parent_scope = parent;
    _next_scope = NULL;
}

Scope::~Scope() {
    if (_next_scope)
	delete _next_scope;

    for (auto it = _list.begin(); it != _list.end(); it++)
	delete it->second;
}

Scope * Scope::newScope() {
    if (_next_scope) {
	cout << "[Error] Next scope already exist." << endl;
	exit(-1);
    }
    _next_scope = new Scope(this);
    return _next_scope;
}

Scope * Scope::getParent() {
    return _parent_scope;
}

void Scope::addSymbol(Symbol * s, ast::Position * pos) {
    if (_list.find(s->getName ()) != _list.end()) {
	throw MultipleDefException(Global::getInstance()->file_name, pos, s->getName ());
	exit(-1);
    }
    _list[s->getName()] = s;
}

Symbol * Scope::getSymbol(string name, ast::Position * pos) {
    auto it = _list.find(name);
    if (it != _list.end())
	return it->second;
    if (_parent_scope)
	return _parent_scope->getSymbol (name, pos);
    throw SymbolNotFoundException(Global::getInstance()->file_name, pos, name);
    exit(-1);
}

string Scope::toString() const {
    stringstream ss;
    for (auto it = _list.begin(); it != _list.end(); it++)
	ss << it->second->toString() << endl;;
    if (_next_scope)
	ss << _next_scope->toString();
    return ss.str ();
}

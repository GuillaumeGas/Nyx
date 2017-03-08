#include "Scope.hpp"
#include "Table.hpp"

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

    if (_parent_scope)
	_parent_scope->_next_scope = NULL;

    for (auto it = _symbolsList.begin(); it != _symbolsList.end(); it++)
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

Scope * Scope::newFunScope () {
    if (_next_scope != NULL) {
	cout << "[Error] Next scope already exist." << endl;
	exit (-1);
    }
    _next_scope = new FunScope (this);
    return _next_scope;
}

Scope * Scope::getParent() {
    return _parent_scope;
}

void Scope::addSymbol(Symbol * s, Position * pos) {
    _symbolsList[s->getName()] = s;
}

void Scope::addFunSymbol (FunSymbol * s, Position * pos) {
    _funSymbolsList[s->getName ()] = s;
}

Symbol * Scope::getSymbol(string name, Position * pos) {
    auto it = _symbolsList.find(name);
    if (it != _symbolsList.end())
	return it->second;
    if (_parent_scope)
	return _parent_scope->getSymbol (name, pos);
    return NULL;
}

FunSymbol * Scope::getFunSymbol (string name, Position * pos) {
    auto it = _funSymbolsList.find (name);
    if (it != _funSymbolsList.end ())
	return it->second;
    return NULL;
}

string Scope::toString() const {
    stringstream ss;
    for (auto it = _symbolsList.begin(); it != _symbolsList.end(); it++)
	ss << it->second->toString() << endl;
    for (auto it = _funSymbolsList.begin (); it != _funSymbolsList.end (); it++)
	ss << it->second->toString () << endl;
    if (_next_scope)
	ss << _next_scope->toString();
    return ss.str ();
}

FunScope::FunScope (Scope * parent) : Scope (parent) {}

Symbol * FunScope::getSymbol(string name, Position * pos) {
    auto it = _symbolsList.find(name);
    if (it != _symbolsList.end())
	return it->second;
    return Table::getInstance ()->getGlobalSymbol (name, pos);
}

FunSymbol * FunScope::getFunSymbol (string name, Position * pos) {
    auto it = _funSymbolsList.find(name);
    if (it != _funSymbolsList.end())
	return it->second;
    return NULL;
}

#include <iostream>
#include <vector>

#include "StaticAnalysis.hpp"
#include "Symbol.hpp"

using namespace nyx;
using namespace symbol;
using namespace std;

StaticAnalysis* StaticAnalysis::_instance = nullptr;

StaticAnalysis* StaticAnalysis::getInstance()
{
    if (_instance == nullptr) {
        _instance = new StaticAnalysis;
    }
    return _instance;
}

StaticAnalysis::StaticAnalysis() {}
StaticAnalysis::~StaticAnalysis() {}

void StaticAnalysis::addUnusedSymbol(string name, Position pos)
{
    _unusedSymbols.push_back(std::make_pair(name, pos));
}

void StaticAnalysis::displayUnusedSymbols() const
{
    for (auto it : _unusedSymbols) {
        cout << "[!] Warning line " << it.second.line << " : symbol " << "'" << it.first << "' not used" << endl;
    }
}
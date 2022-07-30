#include <iostream>
#include <vector>

#include "StaticAnalysis.hpp"

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

void StaticAnalysis::addUnusedSymbol(string symbolName)
{
    _unusedSymbols.push_back(symbolName);
}

void StaticAnalysis::displayUnusedSymbols() const
{
    for (auto it : _unusedSymbols) {
        cout << "[!] Warning : symbol " << "'" << it << "' not used" << endl;
    }
}
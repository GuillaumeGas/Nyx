#include "Program.hpp"
#include "../symbol/Table.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Program::Program () {
    _content = new vector<DeclarationPtr> ();
}

Program::~Program () {
    if (_content)
	delete _content;
}

void Program::execute () {
    _declare ();

    symbol::Table * table = symbol::Table::getInstance ();
    symbol::FunSymbol * main_symbol = table->getFunSymbol (MAIN_FUN_NAME, new DefaultPosition ());
    if (main_symbol == NULL)
	throw MainMissingErrorException ();

    main_symbol->getPtr ()->execute (NULL);
}

void Program::addDeclaration (DeclarationPtr declaration) {
    _content->push_back (declaration);
}

void Program::_declare () {
    for (auto it : *_content)
	it->declare ();
}

void Program::print () {
    for (auto it : *_content)
	it->print (cout);
    cout.flush ();
}

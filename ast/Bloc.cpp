#include "Bloc.hpp"
#include "../symbol/Table.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bloc::Bloc(vector<InstructionPtr> * content) : _content (content), Instruction (new DefaultPosition ()) {}

Bloc::~Bloc() {
    if (_content)
	delete _content;
}

vector<InstructionPtr> * Bloc::getContent () const {
    return _content;
}

void Bloc::interpret() {
    symbol::Table * table = symbol::Table::getInstance ();

    for (InstructionPtr a : *_content)
	a->interpret ();
}

void Bloc::print (ostream & out, int offset) const {
    for(InstructionPtr a : *_content) {
	a->print (out, offset);
	out << endl;
    }
}

BlocPtr Bloc::New (std::vector<InstructionPtr> * content) {
    return std::make_shared<Bloc> (content);
}

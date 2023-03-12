#include "Struct.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Struct::Struct(const string& name, Position* pos, vector<MemberPtr>* membersDecl) : Declaration(pos)
{
    _name = name;
    _members = membersDecl;
}

Struct::~Struct()
{
    if (_members)
        delete _members;
}

void Struct::interpret() {}
void Struct::staticAnalysis() {}
void Struct::declare() {}

string Struct::getName() const {
    return _name;
}

void Struct::setName(const std::string& name) {
    _name = name;
}

void Struct::print(ostream& out, int offset) const {
	shift(out, offset);
	out << "Struct<" << _name << ">";
	out << endl << "{" << endl;
	if (_members)
		for (int i = 0; i < _members->size(); i++) {
			(*_members)[i]->print(out, offset + INDENT);
			out << endl;
		}
	out << "}" << endl << endl;
}
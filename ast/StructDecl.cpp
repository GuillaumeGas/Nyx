#include "StructDecl.hpp"

#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

StructDecl::StructDecl(const string& name, Position* pos, vector<MemberPtr>* membersDecl) : Declaration(pos)
{
    _name = name;
    _members = membersDecl;
}

StructDecl::~StructDecl()
{
    if (_members)
        delete _members;
}

void StructDecl::interpret() {}
void StructDecl::staticAnalysis() {}
void StructDecl::declare()
{
	symbol::StructSymbol* symbol = new symbol::StructSymbol(_name, *_pos);
	symbol::Table::getInstance()->addGlobalSymbol(symbol, _pos);

	for (auto it : *_members)
	{
		symbol->addOrSetMember(it->getVarId()->getName(), it->getVarId());
	}
}

string StructDecl::getName() const {
    return _name;
}

void StructDecl::setName(const std::string& name) {
    _name = name;
}

void StructDecl::print(ostream& out, int offset) const {
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
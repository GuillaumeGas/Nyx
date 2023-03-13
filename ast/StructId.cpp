#include "StructId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

StructId::StructId(string name, Position* pos) : Expression(pos)
{
	_name = name;
}

std::string StructId::getName() const
{
	return _name;
}

void StructId::setName(const std::string name)
{
	_name = name;
}

void StructId::print(std::ostream& out, int offset) const
{
	out << _name;
}
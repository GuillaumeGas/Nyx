#include "StructId.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

StructId::StructId(string name, Position* pos) : Expression(pos)
{
	_name = name;
	_type = new Type("structId");
}

std::string StructId::getName() const
{
	return _name;
}

void StructId::setName(const std::string name)
{
	_name = name;
}

ExpressionPtr StructId::interpretExpression()
{
	return shared_from_this();
}

void StructId::print(std::ostream& out, int offset) const
{
	out << _name;
}
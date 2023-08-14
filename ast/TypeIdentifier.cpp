#include "TypeIdentifier.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

TypeIdentifier::TypeIdentifier(string name, Position* pos) : Expression(pos)
{
	_name = name;
}

std::string TypeIdentifier::getName() const
{
	return _name;
}

void TypeIdentifier::setName(const std::string name)
{
	_name = name;
}

void TypeIdentifier::print(std::ostream& out, int offset) const
{
	out << "TypeIdentifier " << _name;
}

ExpressionPtr TypeIdentifier::interpretExpression()
{
	return shared_from_this();
}
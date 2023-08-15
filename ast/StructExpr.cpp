#include "StructExpr.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

StructExpr::StructExpr(string name, Position* pos) : Expression(pos)
{
	_name = name;
	this->setType(new Type("struct", false));
}

std::string StructExpr::getName() const
{
	return _name;
}

void StructExpr::setName(const std::string name)
{
	_name = name;
}

const std::map<std::string, ExpressionPtr>& StructExpr::getValues() const
{
	return _values;
}

void StructExpr::print(std::ostream& out, int offset) const
{
	out << "TypeIdentifier " << _name;
}

ExpressionPtr StructExpr::interpretExpression()
{
	symbol::Table* table = symbol::Table::getInstance();
	symbol::StructSymbol* symbol = table->getStructSymbol(_name, _pos);

	std::vector<MemberPtr>* members = symbol->getPtr()->getMembers();
	for (auto i = 0; i < members->size(); i++)
	{
		std::string memberName = members->at(i)->getVarId()->getName();
		ExpressionPtr varId = Expression::New<VarId>(memberName, new Position(*_pos));
		_values[memberName] = varId;
	}

	return shared_from_this();
}
#pragma once

#include <iostream>
#include <memory>

#include "Expression.hpp"

namespace nyx
{
	namespace ast
	{
		class TypeIdentifier;
		typedef std::shared_ptr<TypeIdentifier> TypeIdentifierPtr;

		class TypeIdentifier : public Expression
		{
		public:
			TypeIdentifier(std::string name, Position* pos);

			std::string getName() const;
			void setName(const std::string name);

			void print(std::ostream& out, int offset = 0) const;

			ExpressionPtr interpretExpression();

		private:
			std::string _name;
		};
	}
}
#pragma once

#include <iostream>
#include <memory>

#include "Expression.hpp"

namespace nyx
{
	namespace ast
	{
		class StructId;
		typedef std::shared_ptr<StructId> StructIdPtr;

		class StructId : public Expression
		{
		public:
			StructId(std::string name, Position* pos);

			std::string getName() const;
			void setName(const std::string name);

			ExpressionPtr interpretExpression() override;

			void print(std::ostream& out, int offset = 0) const;
		private:
			std::string _name;
		};
	}
}
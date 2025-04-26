#pragma once

#include <iostream>
#include <memory>
#include <map>

#include "Expression.hpp"

namespace nyx
{
	namespace ast
	{
		class StructExpr;
		typedef std::shared_ptr<StructExpr> StructExprPtr;

		class StructExpr : public Expression
		{
		public:
			StructExpr(std::string name, Position* pos);

			std::string getName() const;
			void setName(const std::string name);

			const std::map<std::string, ExpressionPtr>* getValues() const;

			void print(std::ostream& out, int offset = 0) const;

			ExpressionPtr interpretExpression(bool returnSymValue = false);

		private:
			std::string _name;
			std::map<std::string, ExpressionPtr> _values;
			bool _interpreted;
		};
	}
}
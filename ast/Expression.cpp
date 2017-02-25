#include "Expression.hpp"

using namespace std;
using namespace ast;

ExpressionPtr Expression::make (Expression * expr) {
    return make_shared<Expression> (expr);
}

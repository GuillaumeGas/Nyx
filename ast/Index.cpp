#include "Index.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Index::Index (ExpressionPtr e1, ExpressionPtr e2, Position * pos) : Expression (pos) {
    this->e1 = e1;
    this->e2 = e2;
}

void Index::print (ostream & out, int offset) const {
    shift (out, offset);
    e1->print (out);
    out << "[";
    e2->print (out);
    out << "]";
}

ExpressionPtr Index::interpretExpression () {
    // ExpressionPtr left_value = e1->interpretExpression ();
    // ExpressionPtr right_value = e2->interpretExpression ();

    // TYPE left_type = left_value->getType ()->value;
    // TYPE right_type = right_value->getType ()->value;

    // if (left_type != TYPE::ARRAY && left_type != TYPE::STRING)
    // 	throw SemanticErrorException ("Left operand must be an array or a string !", e1->pos);
    // if (right_type != TYPE::INT)
    // 	throw SemanticErrorException ("An index must be an integer !", e2->pos);

    // vector<ExpressionPtr> * vec = left_value->getArray ();
    // int index = right_value->getInt ();

    // if (index < vec->size ()) {
    // 	ExpressionPtr ret = (*vec)[index]->interpretExpression ();
    // 	return ret->clone ();
    // } else {
    // 	throw SemanticErrorException ("Index out of bounds !", e2->pos);
    // }
    return NullExpression ();
}

// TODO !
ExpressionPtr Index::interpretASSIGN (ExpressionPtr e) {
    // vector<Expression*> * vec = left_array->array;

    // delete (*vec)[index_value->getInt ()];
    // (*vec)[index_value->getInt ()] = e->clone ();

    // if (value)
    // 	delete value;
    // value = new Value (*e->getValue ());

    // return NULL;
    return NullExpression ();
}

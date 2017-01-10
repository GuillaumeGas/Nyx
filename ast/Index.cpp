#include "Index.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Index::Index (Expression * e1, Expression * e2, Position * pos) {
    this->e1 = e1;
    this->e2 = e2;
    this->pos = pos;
}

Index::~Index () {
    if (e1)
	delete e1;
    if (e2)
	delete e2;
}

void Index::print (ostream & out, int offset) const {
    shift (out, offset);
    e1->print (out);
    out << "[";
    e2->print (out);
    out << "]";
}

Expression * Index::interpretExpression () {
    e1 = e1->interpretExpression ();
    e2 = e2->interpretExpression ();

    Value * left_value = e1->getValue ();
    TYPE left_type = left_value->getType ()->value;

    Value * right_value = e2->getValue ();
    TYPE right_type = right_value->getType ()->value;

    if (left_type != TYPE::ARRAY && left_type != TYPE::STRING)
	throw SemanticErrorException ("Left operand must be an array or a string !", e1->pos);
    if (right_type != TYPE::INT)
	throw SemanticErrorException ("An index must be an integer !", e2->pos);

    Array * left_array = (Array*) left_value->getPtr ();
    vector<Expression*> * vec = left_array->array;
    int index = right_value->getInt ();

    if (index < vec->size ()) {
	Expression * ret = (*vec)[index];
	value = new Value (*(ret->getValue ()));
    } else {
	throw SemanticErrorException ("Index out of bounds !", e2->pos);
    }
    return this;
}

Expression * Index::interpretASSIGN (Expression * e) {
    Value * array_value = e1->getValue ();
    Value * index_value = e2->getValue ();

    Array * left_array = (Array*) array_value->getPtr ();
    vector<Expression*> * vec = left_array->array;

    delete (*vec)[index_value->getInt ()];
    (*vec)[index_value->getInt ()] = e->clone ();

    if (value)
	delete value;
    value = new Value (*e->getValue ());

    return this;
}

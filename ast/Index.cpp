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

AbstractObject * Index::interpretExpression () {
    AbstractObject * left_value = e1->interpretExpression ();
    AbstractObject * right_value = e2->interpretExpression ();

    TYPE left_type = left_value->getType ()->value;
    TYPE right_type = right_value->getType ()->value;

    if (left_type != TYPE::ARRAY && left_type != TYPE::STRING)
	throw SemanticErrorException ("Left operand must be an array or a string !", e1->pos);
    if (right_type != TYPE::INT)
	throw SemanticErrorException ("An index must be an integer !", e2->pos);

    vector<Expression*> * vec = left_value->getArray ();
    int index = right_value->getInt ();

    if (index < vec->size ()) {
	AbstractObject * ret = (*vec)[index]->interpretExpression ();
	return (AbstractObject*) ret->clone ();
    } else {
	throw SemanticErrorException ("Index out of bounds !", e2->pos);
    }
}

// TODO !
AbstractObject * Index::interpretASSIGN (AbstractObject * e) {
    // vector<Expression*> * vec = left_array->array;

    // delete (*vec)[index_value->getInt ()];
    // (*vec)[index_value->getInt ()] = e->clone ();

    // if (value)
    // 	delete value;
    // value = new Value (*e->getValue ());

    return NULL;
}

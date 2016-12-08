#include "Array.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Array::Array (vector<Expression*> * array, Position * pos) {
    this->pos = pos;
    this->type = new Type ("array", false);
    this->array = array;
}

Array::~Array () {
    if (array != NULL) {
	for (auto it : *array) {
	    if (it)
		delete it;
	}
    }
}

void Array::print (ostream & out, int offset) const {
    out << "[";
    if (array != NULL) {
	for (int i = 0; i < array->size (); i++) {
	    (*array)[i]->print (out);
	    if (i < array->size()-1)
		out << ", ";
	}
    }
    out << "]";
}

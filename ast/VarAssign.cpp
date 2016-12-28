#include "VarAssign.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarAssign::VarAssign (VarId * e1, Expression * e2, Operator * op, Position * pos) : Binop (e1, e2, op, pos) {}

VarAssign::~VarAssign () {}

Expression * VarAssign::interpretExpression () {
    Expression * res = e2->interpretExpression ();

    if (op->value != Op::ASSIGN)
	throw SemanticErrorException ("An operator '=' was expected !", pos);

    symbol::Table * table = symbol::Table::getInstance ();
    symbol::Symbol * symbol = table->getSymbol (((VarId*)e1)->name, pos);

    switch (res->getType ()->value) {
    case TYPE::INT:
	symbol->setValue (res->value->Int);
	break;
    case TYPE::FLOAT:
	symbol->setValue (res->value->Float);
	break;
    case TYPE::CHAR:
	symbol->setValue (res->value->Char);
	break;
    case TYPE::BOOL:
	symbol->setValue (res->value->Bool);
	break;
    case TYPE::STRING:
	symbol->setValue (res->value->Str);
	break;
    default:
	throw SemanticErrorException ("Undefined Type !", pos);
    }
}

void VarAssign::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "VarAssign ";
    Binop::print (out);
}

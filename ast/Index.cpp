#include "Index.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Index::Index(ExpressionPtr e1, ExpressionPtr e2, Position* pos) : Expression(pos), _interpreted(false) {
    this->e1 = e1;
    this->e2 = e2;
}

void Index::print(ostream& out, int offset) const {
    shift(out, offset);
    e1->print(out);
    out << "[";
    e2->print(out);
    out << "]";
}

void Index::declare() {
    e1->declare();
    e2->declare();
}

ExpressionPtr Index::interpretExpression(bool)
{
    if (!_interpreted)
    {
        ExpressionPtr left_value = e1->interpretExpression();
        ExpressionPtr right_value = e2->interpretExpression();

        TYPE left_type = left_value->getType()->value;
        TYPE right_type = right_value->getType()->value;

        if (left_type != TYPE::ARRAY && left_type != TYPE::STRING)
            throw SemanticErrorException("Left operand must be an array or a string !", e1->getPos());
        if (right_type != TYPE::INT)
            throw SemanticErrorException("An index must be an integer !", e2->getPos());

        vector<ExpressionPtr>* vec = left_value->getArray();
        int index = right_value->getInt();

        if (index < vec->size())
        {
            res = (*vec)[index]->interpretExpression();
            this->setType(new Type(*res->getType()));
            _interpreted = true;
        }
        else
        {
            throw SemanticErrorException("Index out of bounds !", e2->getPos());
        }
    }

    return shared_from_this();
}

ExpressionPtr Index::interpretASSIGN(ExpressionPtr e)
{
    ExpressionPtr right = e->interpretExpression();

    TYPE left_type = res->getType()->value;
    TYPE right_type = right->getType()->value;

    if (left_type != right_type)
        throw SemanticErrorException("Left and right operand must be with same type !", res->getPos());

    {
        ExpressionPtr arrayExpr = e1->interpretExpression();
        ExpressionPtr indexExpr = e2->interpretExpression();
        vector<ExpressionPtr>* vec = arrayExpr->getArray();
        int index = indexExpr->getInt();

        res = right->clone();
        vec->at(index) = res;
    }

    return res;
}

ExpressionPtr Index::interpretLE(ExpressionPtr e)
{
    return res->interpretLE(e);
}

ExpressionPtr Index::interpretGE(ExpressionPtr e)
{
    return res->interpretGE(e);
}

ExpressionPtr Index::interpretNE(ExpressionPtr e)
{
    return res->interpretNE(e);
}

ExpressionPtr Index::interpretPLUSEQ(ExpressionPtr e)
{
    return res->interpretPLUSEQ(e);
}

ExpressionPtr Index::interpretMINUSEQ(ExpressionPtr e)
{
    return res->interpretMINUSEQ(e);
}

ExpressionPtr Index::interpretMULEQ(ExpressionPtr e)
{
    return res->interpretMULEQ(e);
}

ExpressionPtr Index::interpretDIVEQ(ExpressionPtr e)
{
    return res->interpretDIVEQ(e);
}

ExpressionPtr Index::interpretMODEQ(ExpressionPtr e)
{
    return res->interpretMODEQ(e);
}

ExpressionPtr Index::interpretLT(ExpressionPtr e)
{
    return res->interpretLT(e);
}

ExpressionPtr Index::interpretGT(ExpressionPtr e)
{
    return res->interpretGT(e);
}

ExpressionPtr Index::interpretEQ(ExpressionPtr e)
{
    return res->interpretEQ(e);
}

ExpressionPtr Index::interpretAND(ExpressionPtr e)
{
    return res->interpretAND(e);
}

ExpressionPtr Index::interpretOR(ExpressionPtr e)
{
    return res->interpretOR(e);
}

ExpressionPtr Index::interpretPLUS(ExpressionPtr e)
{
    return res->interpretPLUS(e);
}

ExpressionPtr Index::interpretMINUS(ExpressionPtr e)
{
    return res->interpretMINUS(e);
}

ExpressionPtr Index::interpretMUL(ExpressionPtr e)
{
    return res->interpretMUL(e);
}

ExpressionPtr Index::interpretDIV(ExpressionPtr e)
{
    return res->interpretDIV(e);
}

ExpressionPtr Index::interpretMOD(ExpressionPtr e)
{
    return res->interpretMOD(e);
}

ExpressionPtr Index::interpretPOINT(ExpressionPtr e)
{
    return res->interpretPOINT(e);
}

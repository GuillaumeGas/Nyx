#include "IfElse.hpp"
#include "../symbol/Table.hpp"


using namespace std;
using namespace nyx;
using namespace ast;

IfElse::IfElse(ExpressionPtr cond, BlocPtr blocIf, Position* pos) : Instruction(pos) {
    _cond = cond;
    _blocIf = blocIf;
}

IfElse::IfElse(ExpressionPtr cond, BlocPtr blocIf, BlocPtr blocElse, Position* pos) : Instruction(pos) {
    _cond = cond;
    _blocIf = blocIf;
    _blocElse = blocElse;
}

IfElse::IfElse(ExpressionPtr cond, BlocPtr blocIf, InstructionPtr elseIf, Position* pos) : Instruction(pos) {
    _cond = cond;
    _blocIf = blocIf;
    _blocElseIf = elseIf;
}

void IfElse::declare() {
    _cond->declare();
    _blocIf->declare();
    _blocElse->declare();
}

void IfElse::interpret() {
    _cond = _cond->interpretExpression();

    symbol::Table* table = symbol::Table::getInstance();

    TYPE condType = _cond->getType()->value;

    if (condType != TYPE::BOOL)
        throw SemanticErrorException("Boolean expression expected !", _cond->getPos());

    if (_cond->getBool() && _blocIf) {
        table->enterBlock();
        _blocIf->interpret();
        table->exitBlock();
    }
    else {
        if (_blocElse) {
            table->enterBlock();
            _blocElse->interpret();
            table->exitBlock();
        }
        else if (_blocElseIf) {
            _blocElseIf->interpret();
        }
    }
}

void IfElse::print(ostream& out, int offset) const {
    shift(out, offset);
    out << "if ";
    _cond->print(out);
    out << " {" << endl;
    _blocIf->print(out, offset + INDENT);
    if (_blocElse) {
        shift(out, offset);
        out << "} else {" << endl;
        _blocElse->print(out, offset + INDENT);
    }
    else if (_blocElseIf) {
        shift(out, offset);
        out << "} else ";
        _blocElseIf->print(out, offset + INDENT);
    }
    shift(out, offset);
    out << "}" << endl;;
}

ExpressionPtr IfElse::getCond() const {
    return _cond;
}

void IfElse::setCond(ExpressionPtr cond) {
    _cond = cond;
}

BlocPtr IfElse::getBlocIf() const {
    return _blocIf;
}

void IfElse::setBlocIf(BlocPtr blocIf) {
    _blocIf = blocIf;
}

BlocPtr IfElse::getBlocElse() const {
    return _blocElse;
}

void IfElse::setBlocElse(BlocPtr blocElse) {
    _blocElse = blocElse;
}

InstructionPtr IfElse::getElseIf() const {
    return _blocElseIf;
}

void IfElse::setElseIf(InstructionPtr elseIf) {
    _blocElseIf = elseIf;
}

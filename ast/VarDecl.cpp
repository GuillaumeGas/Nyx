#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "VarDecl.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

VarDecl::VarDecl(VarIdPtr varId, Position* pos) : Instruction(pos) {
    _type = new Type("undef");
    _varId = varId;
}

VarDecl::VarDecl(Type* type, VarIdPtr varId, Position* pos) : Instruction(pos) {
    _type = type;
    _varId = varId;
}

VarDecl::~VarDecl() {
    if (_type)
        delete _type;
}

Type* VarDecl::getType() const {
    return _type;
}

void VarDecl::setType(Type* type) {
    if (_type)
        delete _type;
    _type = type;
}

VarIdPtr VarDecl::getVarId() const {
    return _varId;
}

void VarDecl::setVarId(VarIdPtr varId) {
    _varId = varId;
}

void VarDecl::declare() {
    symbol::Table* table = symbol::Table::getInstance();
    table->addSymbol(new symbol::Symbol(_varId->getName()), _pos);
}

void VarDecl::interpret() {}

void VarDecl::print(ostream& out, int offset) const {
    shift(out, offset);
    out << "VarDecl ";
    _varId->print(out);
}

ParamPtr VarDecl::New(Type* type, VarIdPtr varId, Position* pos) {
    return std::make_shared<VarDecl>(type, varId, pos);
}

#include "Function.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"
#include "Bloc.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Function::Function(const string& name, Position* pos, Type* type, vector<ParamPtr>* params, BlocPtr content) : Declaration(pos) {
	_type = type;
	_params = params;
	_content = content;
	_name = name;
}

Function::~Function() {
	if (_type)
		delete _type;
	if (_params)
		delete _params;
}

void Function::interpret() {}

void Function::declare() {
	symbol::Table* table = symbol::Table::getInstance();
	table->addFunSymbol(new symbol::FunSymbol(_name, shared_from_this()), _pos);
	table->enterFunBlock(shared_from_this());
}

ExpressionPtr Function::execute(vector<ExpressionPtr>* params) {
	symbol::Table* table = symbol::Table::getInstance();
	table->enterFunBlock(shared_from_this());
	_ret.push_back(NullExpression());

	if (_params != NULL) {
		if (params == NULL || (params->size() != _params->size())) {
			cout << "[!] Invalid parameters" << endl;
			throw - 1;
		}

		for (int i = 0; i < params->size(); i++) {
			ParamPtr param = _params->at(i);
			ExpressionPtr value = params->at(i);
			if (value->getType()->value != param->getType()->value) {
				cout << "[!] Invalid param type !" << endl;
				throw - 1;
			}
			table->addSymbol(new symbol::Symbol(param->getVarId()->getName(), value), param->getPos());
		}
	}
	else {
		if (params != NULL) {
			cout << "[!] Invalid parameter." << endl;
			throw - 1;
		}
	}

	/* We interpret the content function while we don't meet a return statement */
	vector<InstructionPtr>* vec_inst = _content->getContent();

	int i = 0;
	int vec_size = vec_inst->size();
	while (i < vec_size && _ret.back() == NULL) {
		(*vec_inst)[i]->interpret();
		i++;
	}

	table->exitFunBlock();

	ExpressionPtr ret = _ret.back();
	_ret.pop_back();

	return ret;
}

Type* Function::getType() const {
	return _type;
}

void Function::setType(Type* type) {
	if (_type)
		delete _type;
	_type = type;
}

string Function::getName() const {
	return _name;
}

void Function::setName(const std::string& name) {
	_name = name;
}

BlocPtr Function::getContent() const {
	return _content;
}

void Function::setContent(BlocPtr bloc) {
	_content = bloc;
}

ExpressionPtr Function::getRet() const {
	return _ret.back();
}

void Function::setRet(ExpressionPtr ret) {
	_ret.back() = ret;
}

void Function::print(ostream& out, int offset) const {
	shift(out, offset);
	out << _type->toString() << " " << _name << "(";
	if (_params)
		for (int i = 0; i < _params->size(); i++) {
			(*_params)[i]->print(out);
			if (i < _params->size() - 1)
				out << ", ";
		}
	out << ") {" << endl;
	shift(out, offset);
	_content->print(out, offset + INDENT);
	shift(out, offset);
	out << "}" << endl;
}

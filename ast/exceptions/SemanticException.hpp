#pragma once

#include <iostream>
#include "../../global/Position.hpp"
#include "../Object.hpp"
#include "../Operator.hpp"
#include "../Type.hpp"
#include "../../global/Global.hpp"

namespace nyx {
    class SemanticErrorException {
    public:
	SemanticErrorException(Position * pos) throw() : file_name(Global::getInstance()->file_name), pos(pos), msg("") {}
	SemanticErrorException(std::string msg, Position * pos) throw() : file_name(Global::getInstance()->file_name), pos(pos), msg(msg) {}

	virtual std::string toString() const {
	    return "[Error] Semantic error in file " + file_name + " at " + pos->toString() + " : " + msg + ".\n"/* + Global::getInstance()->getLine(pos->line)*/;
	}

    protected:
	std::string file_name;
	Position * pos;
	std::string msg;
    };

    class TypeErrorException : public SemanticErrorException {
    public:
	TypeErrorException(ast::AbstractObject * e1, ast::AbstractObject * e2, Position * pos) throw() : t1(e1->getType ()), t2(e2->getType ()), SemanticErrorException(pos) {}
	TypeErrorException(ast::Type * t1, ast::Type * t2, Position * pos) throw() : t1(t1), t2(t2), SemanticErrorException(pos) {}

	std::string toString() const {
	    return "[Error] Incompatible types in file " + file_name + " at " + pos->toString() + " : " + t1->toString() + " with " + t2->toString() + ".\n    " + Global::getInstance()->getLine(pos->line);
	}

    protected:
	ast::Type * t1;
	ast::Type * t2;
    };
};

#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "Expression.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "VarDecl.hpp"
#include "Object.hpp"

namespace nyx {
    namespace ast {
	typedef AstPtr BlocPtr;
	typedef AstPtr FunctionPtr;

	class Function : public Ast {
	public:
	    Function (Type * type, const std::string & ident, std::vector<VarDeclPtr> * params, BlocPtr content, Position * pos);
	    ~Function ();

	    void registerFunctions ();
	    ExpressionPtr execute (std::vector<ExpressionPtr> * params);
	    void setRet (ExpressionPtr ret);

	    void print (std::ostream & out, int offset = 0) const;

	private:
	    Type * type;
	    std::string name;
	    std::vector<VarDeclPtr> * params;
	    BlocPtr content;
	    ExpressionPtr ret;
	};
    };
};

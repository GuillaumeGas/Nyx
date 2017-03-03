#pragma once

#include <iostream>
#include <memory>

#include "../global/Position.hpp"

#define TODO_SEM(p)					\
    printf ("[!] TODO Semantic : %s\n", p);	\
    exit (-1);

#define INDENT 2

namespace nyx {
    namespace ast {

	class Ast;
	typedef std::shared_ptr<Ast> AstPtr;

	class Ast {
	public:
	    virtual ~Ast();
	    virtual void print(std::ostream & out, int offset = 0) const;

	    virtual void registerFunctions ();
	    virtual void interpret ();

	    template<class T, class... Args>
	    static AstPtr New (Args&&... args) {
		return std::make_shared<T> (args...);
	    }

	    Position * pos;
	protected:
	    void shift (std::ostream & out, int offset) const;
	};
    };
};

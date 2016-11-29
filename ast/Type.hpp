#pragma once

#include <iostream>

namespace nyx {
    namespace ast {
	enum TYPE {
	    INT,
	    CHAR,
	    ERR
	};

	class Type {
	public:
	    Type(std::string name, bool is_basic);
	    ~Type();

	    std::string toString() const;
	    TYPE getType() const;
	    bool isBasic () const;

	    TYPE type;
	    std::string name;
	    bool is_basic;
	};

    };
};

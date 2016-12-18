
#pragma once

#include <iostream>

namespace nyx {
    namespace ast {
	enum TYPE {
	    INT,
	    CHAR,
	    BOOL,
	    FLOAT,
	    STRING,
	    ARRAY,
	    RANGE,
	    ERR
	};

	class Type {
	public:
	    Type (std::string name);
	    Type (std::string name, bool is_basic);
	    ~Type();

	    std::string toString() const;
	    bool isBasic () const;

	    TYPE value;
	    std::string name;
	    bool is_basic;

	private:
	    TYPE getValue() const;
	};

    };
};

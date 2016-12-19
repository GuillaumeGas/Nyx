#pragma once

#include <string>
#include <cstring>

namespace nyx {
    namespace ast {
	union Value {
	    int Int;
	    char Char;
	    float Float;
	    double Double;
	    bool Bool;
	    std::string * Str;

	    static Value * makeValue ();
	};
    };
};

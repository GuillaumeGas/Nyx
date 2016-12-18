#pragma once

#include <string>

namespace nyx {
    namespace ast {
	union Value {
	    int Int;
	    char Char;
	    float Float;
	    double Double;
	    bool Bool;
	    std::string * Str;
	};
    };
};

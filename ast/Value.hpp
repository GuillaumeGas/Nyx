#pragma once

#include <string>
#include <cstring>

#include "Type.hpp"

namespace nyx {
    namespace ast {
	union UValue {
	    int Int;
	    char Char;
	    float Float;
	    double Double;
	    bool Bool;
	    void * Ptr;
	};

	class Value {
	public:
	    Value (int val);
	    Value (char val);
	    Value (float val);
	    Value (double val);
	    Value (bool val);
	    Value (void * ptr);
	    ~Value ();

	    int getInt () const;
	    char getChar () const;
	    float getFloat () const;
	    double getDouble () const;
	    bool getBool () const;
	    void * getPtr () const;

	    void set (int val);
	    void set (char val);
	    void set (float val);
	    void set (double val);
	    void set (bool val);
	    void set (void * ptr);

	    std::string toString () const;

	private:
	    UValue _value;
	    Type * _type;

	    void _init ();
	    void _checkPtr ();
	};
    };
};

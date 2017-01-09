#pragma once

#include <string>
#include <cstring>

#include "Type.hpp"

namespace nyx {
    namespace ast {
	class Expression;
	union UValue {
	    int Int;
	    char Char;
	    float Float;
	    bool Bool;
	    Expression * Ptr; //pour le moment on fou une expression...
	};

	class Value {
	public:
	    Value ();
	    Value (const Value & v);
	    Value (int val);
	    Value (char val);
	    Value (float val);
	    Value (bool val);
	    Value (Expression * ptr);
	    Value (Expression * ptr, const std::string type);
	    ~Value ();

	    int getInt () const;
	    char getChar () const;
	    float getFloat () const;
	    bool getBool () const;
	    Expression * getPtr () const;
	    Type * getType () const;

	    void set (int val);
	    void set (char val);
	    void set (float val);
	    void set (bool val);
	    void set (Expression * ptr);
	    void set (Expression * ptr, const std::string type);

	    std::string toString () const;

	private:
	    UValue _value;
	    Type * _type;
	};
    };
};

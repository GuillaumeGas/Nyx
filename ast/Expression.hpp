#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Ast.hpp"
#include "Type.hpp"

namespace nyx {
    namespace ast {
	class Expression;

	typedef std::shared_ptr<Expression> ExpressionPtr;
	typedef ExpressionPtr NullExpression;
	
	class Expression : public Ast, public std::enable_shared_from_this<Expression> {
	public:
	    virtual ~Expression ();

	    virtual void print (std::ostream & out, int offset = 0) const = 0;

	    template <class T, class... Args>
	    static ExpressionPtr New (Args&&... args) {
		return std::make_shared<T> (args...);
	    }

	    Type * getType () const;
	    void setType (Type * type);

	    virtual bool getBool () const;
	    virtual int getInt () const;
	    virtual char getChar () const;
	    virtual float getFloat () const;
	    virtual std::vector<ExpressionPtr> * getArray () const;
	    virtual ExpressionPtr getRangeBegin () const;
	    virtual ExpressionPtr getRangeEnd () const;
	    // virtual Object * getObject () const;

	    virtual void setBool (bool v);
	    virtual void setInt (int v);
	    virtual void setChar (char v);
	    virtual void setFloat (float v);
	    virtual void setArray (std::vector<ExpressionPtr> * v);
	    virtual void setRangeBegin (ExpressionPtr v);
	    virtual void setRangeEnd (ExpressionPtr v);
	    // virtual void setObject (Object * v);

	    virtual ExpressionPtr clone ();
	    virtual ExpressionPtr interpretExpression();
	    virtual ExpressionPtr interpretASSIGN (ExpressionPtr e);
	    virtual ExpressionPtr interpretLE (ExpressionPtr e);
	    virtual ExpressionPtr interpretGE (ExpressionPtr e);
	    virtual ExpressionPtr interpretNE (ExpressionPtr e);
	    virtual ExpressionPtr interpretPLUSEQ (ExpressionPtr e);
	    virtual ExpressionPtr interpretMINUSEQ (ExpressionPtr e);
	    virtual ExpressionPtr interpretMULEQ (ExpressionPtr e);
	    virtual ExpressionPtr interpretDIVEQ (ExpressionPtr e);
	    virtual ExpressionPtr interpretMODEQ (ExpressionPtr e);
	    virtual ExpressionPtr interpretLT (ExpressionPtr e);
	    virtual ExpressionPtr interpretGT (ExpressionPtr e);
	    virtual ExpressionPtr interpretEQ (ExpressionPtr e);
	    virtual ExpressionPtr interpretAND (ExpressionPtr e);
	    virtual ExpressionPtr interpretOR (ExpressionPtr e);
	    virtual ExpressionPtr interpretPLUS (ExpressionPtr e);
	    virtual ExpressionPtr interpretMINUS (ExpressionPtr e);
	    virtual ExpressionPtr interpretMUL (ExpressionPtr e);
	    virtual ExpressionPtr interpretDIV (ExpressionPtr e);
	    virtual ExpressionPtr interpretMOD (ExpressionPtr e);
	    virtual ExpressionPtr interpretPOINT (ExpressionPtr e);

	    virtual ExpressionPtr interpretUnaryMINUS ();

	    Type * type;
	};
    };
};

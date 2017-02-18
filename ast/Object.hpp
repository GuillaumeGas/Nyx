#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"

/**
   Object file

   I use AbstractObject to describe the members of an expression. Thus, a const int will be an Int object, that inherits from AbstractObject.

   Each object inherits the interpret virtual methods declared in the AbstractObject class :
     - interpretExpression
     - interpretASSIGN...

   An object has a number of references on it, in order to know if we have to delete it at the end of bloc.

   An object has a type, it is determined in the constructor of AbstractObject's child classes.
 */
namespace nyx {
    namespace ast {
	class AbstractObject : public Expression {
	public:
	    AbstractObject ();
	    virtual void print (std::ostream & out, int offset = 0) const = 0;
	    virtual ~AbstractObject ();

	    /**
	       Return the number of elements that references this object
	     */
	    int getNbRef () const;

	    /**
	       Set the number of references of the object
	     */
	    void setNbRef (const int nb);

	    /**
	       Return a pointer to a type of the object
	     */
	    Type * getType () const;

	    /**
	       Virtual method that return a pointer on the object

	       Note : overrided in VarId to return its value and not itself
	     */
	    virtual AbstractObject * getPtr ();

	    /**
	       The following virtual methods are used to get the value of the object according to its type 
	     */
	    virtual bool getBool () const;
	    virtual int getInt () const;
	    virtual char getChar () const;
	    virtual float getFloat () const;
	    virtual std::vector<Expression*> * getArray () const;
	    virtual AbstractObject * getRangeStart () const;
	    virtual AbstractObject * getRangeEnd () const;
	    // virtual Object * getObject () const;

	    virtual void setBool (bool v);
	    virtual void setInt (int v);
	    virtual void setChar (char v);
	    virtual void setFloat (float v);
	    virtual void setArray (std::vector<Expression*> * v);
	    virtual void setRangeStart (AbstractObject * v);
	    virtual void setRangeEnd (AbstractObject * v);
	    // virtual void setObject (Object * v);

	    /**
	       The clone method clone the current object, and call the interpretExpression method on the result before returning it
	       to be sure that the object will be collected by the garbage collector
	     */
	    virtual Expression * clone () = 0;

	    virtual AbstractObject * interpretExpression() = 0;
	    virtual AbstractObject * interpretASSIGN (AbstractObject * e);
	    virtual AbstractObject * interpretLE (AbstractObject * e);
	    virtual AbstractObject * interpretGE (AbstractObject * e);
	    virtual AbstractObject * interpretNE (AbstractObject * e);
	    virtual AbstractObject * interpretPLUSEQ (AbstractObject * e);
	    virtual AbstractObject * interpretMINUSEQ (AbstractObject * e);
	    virtual AbstractObject * interpretMULEQ (AbstractObject * e);
	    virtual AbstractObject * interpretDIVEQ (AbstractObject * e);
	    virtual AbstractObject * interpretMODEQ (AbstractObject * e);
	    virtual AbstractObject * interpretLT (AbstractObject * e);
	    virtual AbstractObject * interpretGT (AbstractObject * e);
	    virtual AbstractObject * interpretEQ (AbstractObject * e);
	    virtual AbstractObject * interpretAND (AbstractObject * e);
	    virtual AbstractObject * interpretOR (AbstractObject * e);
	    virtual AbstractObject * interpretPLUS (AbstractObject * e);
	    virtual AbstractObject * interpretMINUS (AbstractObject * e);
	    virtual AbstractObject * interpretMUL (AbstractObject * e);
	    virtual AbstractObject * interpretDIV (AbstractObject * e);
	    virtual AbstractObject * interpretMOD (AbstractObject * e);
	    virtual AbstractObject * interpretPOINT (AbstractObject * e);

	    virtual AbstractObject * interpretUnaryMINUS ();

	protected:
	    int nb_ref;
	    Type * type;
	};

	class Int : public AbstractObject {
	public:
	    Int(int value, Position * pos);
	    ~Int();

	    int getInt () const;
	    void setInt (int v);

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    AbstractObject * interpretExpression();
	    AbstractObject * interpretLE (AbstractObject * e);
	    AbstractObject * interpretGE (AbstractObject * e);
	    AbstractObject * interpretNE (AbstractObject * e);
	    AbstractObject * interpretLT (AbstractObject * e);
	    AbstractObject * interpretGT (AbstractObject * e);
	    AbstractObject * interpretEQ (AbstractObject * e);
	    AbstractObject * interpretAND (AbstractObject * e);
	    AbstractObject * interpretOR (AbstractObject * e);
	    AbstractObject * interpretPLUS (AbstractObject * e);
	    AbstractObject * interpretMINUS (AbstractObject * e);
	    AbstractObject * interpretMUL (AbstractObject * e);
	    AbstractObject * interpretDIV (AbstractObject * e);
	    AbstractObject * interpretMOD (AbstractObject * e);

	    AbstractObject * interpretUnaryMINUS ();

	private:
	    int value;
	};

	class Char : public AbstractObject {
	public:
	    Char(char value, Position * pos);
	    ~Char();

	    char getChar () const;
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    AbstractObject * interpretExpression ();
	    AbstractObject * interpretLE (AbstractObject * e);
	    AbstractObject * interpretGE (AbstractObject * e);
	    AbstractObject * interpretNE (AbstractObject * e);
	    AbstractObject * interpretLT (AbstractObject * e);
	    AbstractObject * interpretGT (AbstractObject * e);
	    AbstractObject * interpretEQ (AbstractObject * e);
	    AbstractObject * interpretAND (AbstractObject * e);
	    AbstractObject * interpretOR (AbstractObject * e);
	    AbstractObject * interpretPLUS (AbstractObject * e);
	    AbstractObject * interpretMINUS (AbstractObject * e);
	    AbstractObject * interpretMUL (AbstractObject * e);
	    AbstractObject * interpretDIV (AbstractObject * e);
	    AbstractObject * interpretMOD (AbstractObject * e);

	    AbstractObject * interpretUnaryMINUS ();

	private:
	    char value;
	};

	class Float : public AbstractObject {
	public:
	    Float (float value, Position * pos);
	    ~Float ();

	    float getFloat () const;
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    AbstractObject * interpretExpression ();
	    AbstractObject * interpretLE (AbstractObject * e);
	    AbstractObject * interpretGE (AbstractObject * e);
	    AbstractObject * interpretNE (AbstractObject * e);
	    AbstractObject * interpretLT (AbstractObject * e);
	    AbstractObject * interpretGT (AbstractObject * e);
	    AbstractObject * interpretEQ (AbstractObject * e);
	    AbstractObject * interpretAND (AbstractObject * e);
	    AbstractObject * interpretOR (AbstractObject * e);
	    AbstractObject * interpretPLUS (AbstractObject * e);
	    AbstractObject * interpretMINUS (AbstractObject * e);
	    AbstractObject * interpretMUL (AbstractObject * e);
	    AbstractObject * interpretDIV (AbstractObject * e);

	    AbstractObject * interpretUnaryMINUS ();

	private:
	    float value;
	};

	class Bool : public AbstractObject {
	public:
	    Bool(bool value, Position * pos);
	    ~Bool();

	    bool getBool () const;
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    AbstractObject * interpretExpression ();
	    AbstractObject * interpretLE (AbstractObject * e);
	    AbstractObject * interpretGE (AbstractObject * e);
	    AbstractObject * interpretNE (AbstractObject * e);
	    AbstractObject * interpretLT (AbstractObject * e);
	    AbstractObject * interpretGT (AbstractObject * e);
	    AbstractObject * interpretEQ (AbstractObject * e);
	    AbstractObject * interpretAND (AbstractObject * e);
	    AbstractObject * interpretOR (AbstractObject * e);
	    AbstractObject * interpretPLUS (AbstractObject * e);
	    AbstractObject * interpretMINUS (AbstractObject * e);
	    AbstractObject * interpretMUL (AbstractObject * e);
	    AbstractObject * interpretDIV (AbstractObject * e);
	    AbstractObject * interpretMOD (AbstractObject * e);

	    AbstractObject * interpretUnaryMINUS ();

	private:
	    bool value;
	};

	class Array : public AbstractObject {
	public:
	    Array ();
	    Array (std::vector<Expression*> * array, Position * pos);
	    ~Array ();

	    std::vector<Expression*> * getArray () const;
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    AbstractObject * interpretExpression ();
	    // AbstractObject * interpretAND (AbstractObject * e);
	    // AbstractObject * interpretOR (AbstractObject * e);
	    AbstractObject * interpretPLUS (AbstractObject * e);

	protected:
	    std::vector<Expression*> * array;
	};

	class String : public Array {
	public:
	    String (std::string str, Position * pos);
	    String (const String & str, Position * pos);

	    void print (std::ostream & out, int offset = 0) const;

	    AbstractObject * interpretExpression ();
	};

	class Range : public AbstractObject {
	public:
	    Range (Expression * start, Expression * end, Position * pos);
	    ~Range ();

	    AbstractObject * getRangeStart () const;
	    AbstractObject * getRangeEnd () const;
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * clone ();
	    AbstractObject * interpretExpression ();

	    Expression * start;
	    Expression * end;
	};

    };
};

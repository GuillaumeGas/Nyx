#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "../symbol/GarbageCollector.hpp"

namespace nyx {
    namespace ast {
	class AbstractObject : public Expression {
	public:
	    AbstractObject ();
	    virtual void print (std::ostream & out, int offset = 0) const = 0;
	    virtual ~AbstractObject ();

	    int getNbRef () const;
	    void setNbRef (const int nb);
	    Type * getType () const;
	    virtual AbstractObject * getPtr ();

	    virtual bool getBool () const;
	    virtual int getInt () const;
	    virtual char getChar () const;
	    virtual float getFloat () const;
	    virtual std::vector<Expression*> * getArray () const;
	    virtual AbstractObject * getRangeStart () const;
	    virtual AbstractObject * getRangeEnd () const;
	    // virtual Object * getObject () const;

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

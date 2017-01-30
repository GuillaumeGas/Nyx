#pragma once

#include <iostream>
#include <list>

#include "../ast/Object.hpp"

namespace nyx {
    namespace symbol {
	/**
	   The struct is used to determine if an object is still referenced
	   It also call the destructor of the object (because the remove_if function of std::list doesn't call it automatically)
	 */
	struct deleteUnreferenced {
	    bool operator () (const ast::AbstractObject * object);
	};

	/**
	   The garbage collector keep a pointer of each object (Int, Char, ...)
	 */
	class GarbageCollector {
	public:
	    static GarbageCollector * getInstance ();
	    ~GarbageCollector ();

	    /**
	       Add an object to the garbage collector
	     */
	    void addObject (ast::AbstractObject * object);
	    
	    /**
	       Called when we quit a scope, delete every Object with a ref <= 0
	     */
	    void free ();

	    /**
	       Delete all the allocated objects
	     */
	    void freeAll ();

	private:
	    static GarbageCollector * instance;
	    GarbageCollector ();

	    std::list <ast::AbstractObject *> objects;
	};
    };
};

#include "GarbageCollector.hpp"

using namespace std;
using namespace nyx;
using namespace symbol;

bool deleteUnreferenced::operator () (const ast::AbstractObject * object) {
    if (object->getNbRef () <= 0) {
	delete object;
	return true;
    }
    return false;
}

GarbageCollector * GarbageCollector::instance = NULL;

GarbageCollector::GarbageCollector () {}

GarbageCollector * GarbageCollector::getInstance () {
    if (instance == NULL)
	instance = new GarbageCollector ();
    return instance;
}

void GarbageCollector::addObject (ast::AbstractObject * object) {
    objects.push_back (object);
}

void GarbageCollector::freeAll () {
    for (auto it : objects) {
	delete it;
    }
}

void GarbageCollector::free () {
    // we remove all the objects with a number of reference <= 0
    objects.remove_if (deleteUnreferenced ());
}

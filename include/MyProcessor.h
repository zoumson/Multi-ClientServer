#ifndef MY_PROCESSOR_H
#define MY_PROCESSOR_H
#include "MyServer.h"

/**
 * Implementation of a Processor to deal with a client request
 *
 * MyProcessor is an abstract class, due to the  
 * the existence of the pure virtual member function process (= 0)
 * process needs to be overriden by derived class otherwise compile error
 * no objects of class MyProcessor can be directly created
 * virtual function avoid function overloading
 * At runtime the os uses dynamic binding to determine the type of the object
 * Function that are not virtual uses static binding, 
 * the type of the object is defined at compile time 
 * For a base class with a derived make the base class desctucort virtual
 * Then for every derived class define its destructor appropriately
 * Don't let the base class destructor clean the object when it's out of the current scope
 * 
 */
class MyProcessor
{
public:

	virtual void process(MyServer serverProcessingAcceptedConnexion) = 0;

};

#endif /*MY_PROCESSOR_H */

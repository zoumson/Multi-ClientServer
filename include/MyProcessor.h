

/*
* License plate detection
* See COPYRIGHT file at the top of the source tree.
*
* This product includes software developed by the
* STARGUE Project (http://www.stargue.org/).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the STARGUE License Statement and
* the GNU General Public License along with this program. If not,
* see <http://www.lsstcorp.org/LegalNotices/>.
*/

/**
 * @file MyProcessor.h
 *
 * @brief An abstract class used by the server to process a client request
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */


#ifndef MY_PROCESSOR_H
#define MY_PROCESSOR_H
#include "MyServer.h"

namespace za{
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

	virtual void process(za::MyServer serverProcessingAcceptedConnexion) = 0;

};
}

#endif /*MY_PROCESSOR_H */



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
 * @file ProcessSingleClient.h
 *
 * @brief This customer service is used to give response to a client
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */

#ifndef PROCESS_SINGLE_CLIENT_H
#define PROCESS_SINGLE_CLIENT_H
#include "MyProcessor.h"

namespace za{
/**
 * Implementation of a derived class used to serve the client
 * The parent class is MyProcessor, an abstract class
 */
class ProcessSingleClient:public za::MyProcessor
{
public:
	/* ============================================================================
	* Data Memeber Declaration
	* ============================================================================
	*/
	//none


	/* ============================================================================
	* Member Function Declaration
	* ============================================================================
	*/
	void process(za::MyServer _serverProcessingAcceptedConnexion_);

};
}
#endif /*PROCESS_SINGLE_CLIENT_H */


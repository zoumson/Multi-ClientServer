

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
 * @file MyThread.h
 *
 * @brief A thread used by the server to handle client
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */

#ifndef MY_THREAD_H
#define MY_THREAD_H

#include <pthread.h>
#include "MyProcessor.h"
#include "MyServer.h"

namespace za{
/**
 * Implementation of a thread to handle multiple
 * client that wants to connect to a single server
 */
class MyThread
{

public:


	/* ============================================================================
	* Data Memeber Declaration
	* ============================================================================
	*/
	pthread_t threadID;
	MyProcessor *processor;

	/* ============================================================================
	* Member Function Declaration
	* ============================================================================
	*/
	za::MyServer serverProcessingAcceptedConnexion;
	void createMyThread();
	static void *functionThread(void *arg);
	MyThread(MyProcessor * _processor_, za::MyServer& _servserverProcessingAcceptedConnexion_);
};
}
#endif /*MY_THREAD_H */
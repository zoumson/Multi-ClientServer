

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
 * @file MyServer.h
 *
 * @brief A client to send a request to a server
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */

#ifndef MY_SERVER_H
#define MY_SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <cstddef>
#include <Manager.h>
#include "GetLocalAddress.h"


namespace src = boost::log::sources;


/**
 * Implementation of a server
 * This server uses a TCP/IP communication model
 * to exchange information with multiple clients
 * using the multi-threads fashion
 */
class MyServer
{
private:

	/* ============================================================================
	* Data Memeber Declaration
	* ============================================================================
	*/
	int socketListenToConnexion;
	int socketProcessAcceptedConnexion;
	bool isConnexionActive;
	unsigned short MAX_CONNEXION;
	unsigned short serverPortNumber;
	unsigned short  clientPortNumber;
	
	ssize_t numberOfByteReadFromBuffer;// [-1, +inf]
	char clientIPv4[INET_ADDRSTRLEN +1];
	socklen_t clientAddressLength;
	socklen_t serverAddressLength;
	char buffer[1024];
	std::string serverIPv4;
	struct sockaddr_in serverAddrress;
	struct sockaddr_in clientAddress;
	const char* logName;
	Manager logManager;
	my_logger::logger_type log = my_logger::get();

public:

	/* ============================================================================
	* Member Function Declaration
	* ============================================================================
	*/
	MyServer();
	MyServer(unsigned short _portNumber_, unsigned short _max_connexion_);
	int createServerForBindAndListen();
	int bindServerToPortNumber();
	int listenToNewClientConnexion();
	int acceptToMakeConnexionWithClient();
	int sendResponseToClient(std::string &message, int status);
	int sendResponseToClient(std::string &&message, int status);
	int readIncomingMessageFromClient();
	int getPort();
	int showMaxConnexion();
	int showServerPort();
	int showServerIP();
	int getClientAddress();
	int showClientPort();
	int showClientIP();
	int closeAcceptedConnexion();
	int closeListenningSocket();
	int setLog(std::string& _logName_);
	int setLog(std::string&& _logName_);

};

#endif /* MY_SERVER_H */

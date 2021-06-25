

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
 * @file MyClient.h
 *
 * @brief A client to send a request to a server
 *
 * @author Adama Zouma
 * 
 * @Contact: stargue49@gmail.com
 *
 */
#ifndef MY_CLIENT_H
#define MY_CLIENT_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
//#include "Clock.h"
#include <Manager.h>
#include <tuple>
#include <time.h>
namespace za{
/**
 * Implementation of a client
 * This client uses a TCP/IP communication model
 * to connect to a server
 * Once connected the client sends the current 
 * time information to the server
 * the client also wait for the server response
 */
class MyClient
{
private:

	/* ============================================================================
	* Data Memeber Declaration
	* ============================================================================
	*/
	int socketConnectToClient_;
	unsigned short serverPortNumber_;
	int numberOfByteOfBuffer_;

	//Clock clock;

	struct sockaddr_in serverAddress_;
	struct hostent *serverIP_;
	za::Manager logManager;
	za::my_logger::logger_type log = za::my_logger::get();
	char buffer[1024];

public:

	/* ============================================================================
	* Member Function Declaration
	* ============================================================================
	*/

	MyClient(char *_serverIP_, unsigned short _serverPort_);
	int createClientForConnexion();
	int connectClientToServer();
	int sendRequestToServer();
	int receiveResponseFromServer();
	int closeConnexion();
	int setLog(std::string& _logName_);
	int setLog(std::string&& _logName_);
	std::tuple <std::string, std::string> getCurrentTime();
	// Setter and Getter socketConnectToClient

	auto socketConnectToClient() const& -> const int& { return socketConnectToClient_; }
	auto socketConnectToClient() &      -> int&       { return socketConnectToClient_; }
	auto socketConnectToClient() &&     -> int&&      { return std::move(socketConnectToClient_); }
	// Setter and Getter serverPortNumber

	auto serverPortNumber() const& -> const unsigned short& { return serverPortNumber_; }
	auto serverPortNumber() &      -> unsigned short&       { return serverPortNumber_; }
	auto serverPortNumber() &&     -> unsigned short&&      { return std::move(serverPortNumber_); }

	// Setter and Getter numberOfByteOfBuffer

	auto numberOfByteOfBuffer() const& -> const int& { return numberOfByteOfBuffer_; }
	auto numberOfByteOfBuffer() &      -> int&       { return numberOfByteOfBuffer_; }
	auto numberOfByteOfBuffer() &&     -> int&&      { return std::move(numberOfByteOfBuffer_); }

	// Setter and Getter socketConnectToClient

	auto serverAddress() const& -> const sockaddr_in& { return serverAddress_; }
	auto serverAddress() &      -> sockaddr_in&       { return serverAddress_; }
	auto serverAddress() &&     -> sockaddr_in&&      { return std::move(serverAddress_); }
	// Setter and Getter socketConnectToClient
};
}

#endif /* MY_CLIENT_H */
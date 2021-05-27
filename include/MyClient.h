#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include "Clock.h"
#include <Manager.h>

class MyClient
{
private:
	int socketConnectToClient_;
	unsigned short serverPortNumber_;
	int numberOfByteOfBuffer_;

	Clock clock;

	struct sockaddr_in serverAddress_;
	struct hostent *serverIP_;
	Manager logManager;
	my_logger::logger_type log = my_logger::get();
	char buffer[1024];
public:
	MyClient(char *_serverIP_, unsigned short _serverPort_);
	int createClientForConnexion();
	int connectClientToServer();
	int sendRequestToServer();
	int receiveResponseFromServer();
	int closeConnexion();
	int setLog(std::string& _logName_);
	int setLog(std::string&& _logName_);
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

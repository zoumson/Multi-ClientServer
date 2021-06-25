#include "MyClient.h"


namespace za{
MyClient::MyClient(char *_serverIP_, unsigned short _serverPort_)
{
	BOOST_LOG_SEV(log, report)<<"Client initializing ...\n";

	serverPortNumber() = _serverPort_;
	this->createClientForConnexion();

	serverIP_ = gethostbyname(_serverIP_);
	if (serverIP_ == NULL)
	{
		BOOST_LOG_SEV(log, report)<<"Error host not found"
					<<strerror(h_errno)<<"\n";

	}
	else
	{
		BOOST_LOG_SEV(log, report)<<"Client initialized\n";
	}

	this->connectClientToServer();
}

// Creation of a socket
int MyClient::createClientForConnexion()
{
	int returnValue = 0;

	BOOST_LOG_SEV(log, report) << "Creating a client socket ...\n";

	socketConnectToClient_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socketConnectToClient_ < 0)
	{
		returnValue = -200000; 
		BOOST_LOG_SEV(log, error) <<"Error while creating a client socket"
	<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 
	}
	else
	{
		BOOST_LOG_SEV(log, report) << "A client socket created\n";

	}
	return returnValue;
}

// Connect to a server
int MyClient::connectClientToServer()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "Connecting to a server ...\n";

	bzero((char *) &serverAddress(), sizeof(serverAddress()));

    serverAddress().sin_family = AF_INET;

    bcopy((char *)serverIP_->h_addr, (char *)&serverAddress().sin_addr.s_addr,
	serverIP_->h_length);

    serverAddress().sin_port = htons(serverPortNumber());

    if (connect(socketConnectToClient_,(struct sockaddr *) &serverAddress(), 
	sizeof(serverAddress())) < 0)
    {
		returnValue = -200001; 
    	BOOST_LOG_SEV(log, error)<<"Error while connecting to a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  

    }
	else
	{
		BOOST_LOG_SEV(log, report) << "A client connected to a server\n";
	}
	return returnValue;
}

// Send a message to a server
int MyClient::sendRequestToServer()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "A Client sending a request ...\n";
	//std::string aux = clock.currentDateTime();
	std::string data = std::get<1>(getCurrentTime());

	numberOfByteOfBuffer() = write(socketConnectToClient_,data.c_str(),18);
	if (numberOfByteOfBuffer() < 0 )
	{
		returnValue = -200002; 		
		BOOST_LOG_SEV(log, error)<<"Error of sending a request to a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  
	}
	else
	{
		BOOST_LOG_SEV(log, report) << "Request sent to a server\n";

	}
	return returnValue;

}

// Receive response from the server
int MyClient::receiveResponseFromServer()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "A Client receiving a response ...\n";

    bzero(buffer,1024);
     numberOfByteOfBuffer() = read(socketConnectToClient_,buffer,1023);
    if (numberOfByteOfBuffer() < 0)
     {
		returnValue = -200003; 	
     	BOOST_LOG_SEV(log, error)<<"Fail to receive response from a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  

     }
	 {
		 BOOST_LOG_SEV(log, report) << "Response from a server\n";
		 BOOST_LOG_SEV(log, report) << buffer << "\n";
	 }
	return returnValue;

}

int MyClient::closeConnexion()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "A Client closing a connexion ...\n";
	if(close(socketConnectToClient_) < 0)
	{
		returnValue = -200004; 
     	BOOST_LOG_SEV(log, error)<<"Fail to close a connexion with a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  

	}
	else
	{
     	BOOST_LOG_SEV(log, report)<<"Connexion with a server closed\n";

	}
	return returnValue;
}
// setlog
int MyClient::setLog(std::string& _logName_)
{
	int returnValue = 0;
	this->logManager.set_log_file( &_logName_[0]);
	return returnValue;
}
// Setlog
int MyClient::setLog(std::string&& _logName_)
{
	int returnValue = 0;
	this->logManager.set_log_file( &_logName_[0]);
	return returnValue;
}

std::tuple <std::string, std::string> MyClient::getCurrentTime()
{
    std::time_t now = std::time(NULL);
    std::tm * ptm = std::localtime(&now);
    char buffer1[32], buffer2[32];
    // Format: Mo, 15.06.2009 20:20:00
    std::strftime(buffer1, 32, "%d_%m_%Y_%H_%M_%S_", ptm);
    std::strftime(buffer2, 32, "%H:%M:%S", ptm);
	return std::make_tuple(std::string(buffer1), std::string(buffer2));
}
}


#include "MyServer.h"

// Define the default constructor
MyServer::MyServer():MyServer(0, 5){}
// Define a custon constructor
MyServer::MyServer(unsigned short _portNumber_, unsigned short _max_connexion_):
serverPortNumber(_portNumber_), MAX_CONNEXION(_max_connexion_)
{

	this->serverAddressLength = sizeof(this->serverAddrress);
	memset(&serverAddrress, 0, sizeof(serverAddrress));
	memset(&clientAddress, 0, sizeof(clientAddress));
    this->serverAddrress.sin_family = AF_INET;
    this->serverAddrress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddrress.sin_port = htons(this->serverPortNumber);
	clientAddressLength = sizeof(clientAddress);
	this->isConnexionActive = false;
}
// createServerForBindAndListen a socket 
int MyServer::createServerForBindAndListen()
{
	this->showMaxConnexion();
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "Creating a server socket ...\n";

	socketListenToConnexion = socket(AF_INET, SOCK_STREAM, 0);

	
	if (socketListenToConnexion < 0)
	{
		returnValue = -100000;		
		BOOST_LOG_SEV(log, error)<<"Error while creating a server socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";

	}
	else
	{
		
		BOOST_LOG_SEV(log, report) << "A client socket created\n";

	}
	return returnValue;
}

// Bind a socket to a specific port number
int MyServer::bindServerToPortNumber()
{
	int returnValue = 0;
	
	BOOST_LOG_SEV(log, report) << "Binding to a local port ...\n";

    if (bind(this->socketListenToConnexion,
			(struct sockaddr *) &this->serverAddrress, 
					sizeof(this->serverAddrress)) < 0)
    {
 		returnValue = -100001;   	
		BOOST_LOG_SEV(log, error)<<"Error while binding a socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
    }
	else
	{
		
		BOOST_LOG_SEV(log, report) << "Bind success\n";
	}
	return returnValue;
}

// Listen to a new connexion 
int MyServer::listenToNewClientConnexion()
{
	int returnValue = 0;

	BOOST_LOG_SEV(log, report) << "Listenning to a new connexion...\n";
  	if (listen(socketListenToConnexion, this->MAX_CONNEXION) < 0)
    {
		returnValue = -100002;		
    	BOOST_LOG_SEV(log, error)<<"Error while Listenning to a new connexion"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
    }
	else
	{
		BOOST_LOG_SEV(log, report) << "A client connected to a server\n";
	}
	return returnValue;
}

// Accept a connexion
int MyServer::acceptToMakeConnexionWithClient()
{
	int returnValue = 0;

	BOOST_LOG_SEV(log, report)<< "Accepting a connexion...\n";
    socketProcessAcceptedConnexion = accept(socketListenToConnexion,
										(struct sockaddr *)&clientAddress,
										&clientAddressLength);
     if (socketProcessAcceptedConnexion < 0)
     {
		returnValue = -100003;	
     	BOOST_LOG_SEV(log, error)<<"Error while accepting a connexion"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
     }
	 else
	 {
     	BOOST_LOG_SEV(log, report)<<"Connexion accepted\n";
		this->getClientAddress();
		this->showClientIP();
		this->showClientPort();
		this->isConnexionActive = true;

	 }
	return returnValue;
}

// Read a client message
int MyServer::readIncomingMessageFromClient()
{
	int returnValue = 0;
	if(this->isConnexionActive)
	{
		memset(buffer, 0, sizeof(buffer));
		numberOfByteReadFromBuffer = read(socketProcessAcceptedConnexion, buffer, 
											sizeof(buffer));
		if (numberOfByteReadFromBuffer < 0)
		{
			returnValue = -100004;			 
			BOOST_LOG_SEV(log, error)<<"Error while reading client message"
				<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
		}
		else if(numberOfByteReadFromBuffer == 0)
		{
			BOOST_LOG_SEV(log, report) << "Closing connexion with client: "
									<<socketProcessAcceptedConnexion<<"\n";
			this->closeAcceptedConnexion();
		}
		else
		{
			BOOST_LOG_SEV(log, report)<< "Time received from the client "
				<< socketProcessAcceptedConnexion <<": "<< buffer <<"\n";

		}		
	}

	return returnValue;
}

// Send back a message to the client
int MyServer::sendResponseToClient(std::string &message, int status)
{
	int returnValue = 0;
	if(this->isConnexionActive)
		{
			switch (status)
			{
			case 200:
				numberOfByteReadFromBuffer = write(socketProcessAcceptedConnexion,
											&message[0],18);
				if (numberOfByteReadFromBuffer < 0)
				{
					returnValue = -100006;		
					BOOST_LOG_SEV(log, error)<<"Fail to send back message to the client"
						<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
					
				}			
				break;
			case 400:
				BOOST_LOG_SEV(log, error)<<"Connexion with client closed.\n";			
			
			default:
				BOOST_LOG_SEV(log, error)<<"Unknown sendResponseToClient ERROR.\n";

				break;
			}
	}
	
	return returnValue;
}
// Send back a message to the client
int MyServer::sendResponseToClient(std::string &&message, int status)
{
	int returnValue = 0;
	if(this->isConnexionActive)
	{
			switch (status)
			{
				case 200:
					numberOfByteReadFromBuffer = write(socketProcessAcceptedConnexion,
												&message[0],18);
					if (numberOfByteReadFromBuffer < 0)
					{
						returnValue = -100006;		
						BOOST_LOG_SEV(log, error)<<"Fail to send back message to the client"
							<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
						
					}			
					break;
				case 400:
					BOOST_LOG_SEV(log, error)<<"Connexion with client closed.\n";
				
				default:
					BOOST_LOG_SEV(log, error)<<"Unknown sendResponseToClient ERROR.\n";

					break;
			}
	}
	
	return returnValue;
}


//Close connexion
int MyServer::getPort()
{
	int returnValue = 0;

    if( getsockname(socketListenToConnexion, (struct sockaddr *)&serverAddrress, 
		&serverAddressLength) < 0)
		{
			returnValue = -100007;	
			BOOST_LOG_SEV(log, error)<<"Fail to get server port number from getsockname"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";						
	}
	else
	{
		returnValue = ntohs(serverAddrress.sin_port);  // get the port number
		if(returnValue < 0)
		{
			returnValue = -100008;	
			BOOST_LOG_SEV(log, error)<<"ntos error with sin_port"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";					
		}
		else
		{
			this->serverPortNumber = (unsigned short) returnValue;
		}
	}

    
    return returnValue;
}
int MyServer::getClientAddress()
{
	int returnValue = 0;
    if(inet_ntop(AF_INET, &this->clientAddress.sin_addr, this->clientIPv4, 
				INET_ADDRSTRLEN) == NULL)
    {
       	returnValue = -100009; 
        BOOST_LOG_SEV(log, error) << "unable to convert IP from binary to text "
					<<"dotted-decimal format"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 
    }
	return returnValue;

}
int MyServer::showClientPort()
{
	int returnValue = 0;
	this->clientPortNumber = ntohs(this->clientAddress.sin_port);
    if(this->clientPortNumber < 0)
    {
       	returnValue = -100010; 
        BOOST_LOG_SEV(log, error) << "unable to convert Port Number from network to host order "
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";    
    }
	else
	{
		BOOST_LOG_SEV(log, report) << "Client Port Number: ["<< this->clientPortNumber<<"]\n";

	}
	return returnValue;

}
int MyServer::showClientIP()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "Client IP: ["<< this->clientIPv4<<"]\n";
	return returnValue;
}
int MyServer::showServerPort()
{
	int returnValue = 0;
	this->getPort();
	BOOST_LOG_SEV(log, report) << "Server Port Number: ["<< this->serverPortNumber<<"]\n";
	return returnValue;
}
int MyServer::showServerIP()
{
	int returnValue = 0;
	if( getLocalAddress(this->serverIPv4) < 0)
	{
       	returnValue = -100011; 
        BOOST_LOG_SEV(log, error) << "Fail to get server address from getLocalAddress"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 
	}
	else
	{
		BOOST_LOG_SEV(log, report) << "Server IP: ["<< this->serverIPv4<<"]\n";
	}
	return returnValue;
}
int MyServer::showMaxConnexion()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report) << "Server max connexion: ["<< this->MAX_CONNEXION<<"]\n";
	return returnValue;
}
int MyServer::closeAcceptedConnexion()
{
	int returnValue = 0;
	BOOST_LOG_SEV(log, report)<< "A Server closing an accpeted connexion ...\n";
	if(close(socketProcessAcceptedConnexion) < 0)
	{
       	returnValue = -100012; 
     	BOOST_LOG_SEV(log, error)<<"Fail to close a connexion with a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 

	}
	else
	{
     	BOOST_LOG_SEV(log, report) <<"Accepted connexion closed\n";
		 this->isConnexionActive = false;

	}
	return returnValue;
}
int MyServer::closeListenningSocket()
{
	int returnValue = 0;


		BOOST_LOG_SEV(log, report) << "A Server stopping listen to a new connexion ...\n";
		if(close(socketListenToConnexion) < 0)
		{
		returnValue = -100013; 
     	BOOST_LOG_SEV(log, error)<<"Fail to close a listenning socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  
	

		}
		else
		{
     	BOOST_LOG_SEV(log, report)<<"Listenning socket closed\n";
		BOOST_LOG_SEV(log, report) << "A server stopped listen to a new connexion\n";	

		}
		


	return returnValue;
}


// setlog
int MyServer::setLog(std::string& _logName_)
{
	int returnValue = 0;
	this->logManager.set_log_file( &_logName_[0]);
	return returnValue;
}
// Setlog
int MyServer::setLog(std::string&& _logName_)
{
	int returnValue = 0;
	this->logManager.set_log_file( &_logName_[0]);
	return returnValue;
}

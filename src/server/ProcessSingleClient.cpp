#include "ProcessSingleClient.h"
#include <unistd.h>


void ProcessSingleClient::process(MyServer _serverProcessingAcceptedConnexion_)
{
	bool flag = true;

	while(flag)
	{
	if(_serverProcessingAcceptedConnexion_.readIncomingMessageFromClient() >= 0)
	{
		_serverProcessingAcceptedConnexion_.sendResponseToClient("sucess", 200);
		usleep(6000000);
	} 
	else 
	{
		_serverProcessingAcceptedConnexion_.sendResponseToClient("fail", 400);		
		flag = false;
		
	}
	}
}

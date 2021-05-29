#ifndef PROCESS_SINGLE_CLIENT_H
#define PROCESS_SINGLE_CLIENT_H
#include "MyProcessor.h"


class ProcessSingleClient:public MyProcessor
{
public:
	void process(MyServer _serverProcessingAcceptedConnexion_);
};

#endif /*PROCESS_SINGLE_CLIENT_H */


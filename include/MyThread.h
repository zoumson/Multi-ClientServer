//#include <iostream>
#include <pthread.h>
#include "MyProcessor.h"
#include "MyServer.h"


class MyThread
{

public:

	pthread_t threadID;
	MyProcessor *processor;
	MyServer serverProcessingAcceptedConnexion;
	void createMyThread();
	static void *functionThread(void *arg);

	MyThread(MyProcessor * _processor_, MyServer& _servserverProcessingAcceptedConnexion_);
};

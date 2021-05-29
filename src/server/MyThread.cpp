#include "MyThread.h"



void *MyThread::functionThread(void *arg)
{
	MyThread * myThread = (MyThread *) arg;

	myThread->processor->process(myThread->serverProcessingAcceptedConnexion);
	return NULL;
}

void MyThread::createMyThread()
{
	pthread_create(&this->threadID, NULL, &this->functionThread, this);
}

MyThread::MyThread(MyProcessor *_processor_, MyServer& _servserverProcessingAcceptedConnexion_)
{
	processor = _processor_;
	serverProcessingAcceptedConnexion = _servserverProcessingAcceptedConnexion_;
}

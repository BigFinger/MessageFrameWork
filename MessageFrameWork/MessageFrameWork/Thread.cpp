#include "Thread.h"
#include <process.h>

Thread::Thread(const char *szThreadName){
	this->task = this;
	this->started = false;
	this->joined = false;
	this->threadHandle = 0;
	this->threadId = 0;

	if (szThreadName != NULL)
	{
		strncpy(mThreadName, szThreadName, 31);
		mThreadName[31] = 0;
	}
	else
	{
		mThreadName[0] = 0;
	}
}

Thread::~Thread(){}

void Thread::start(){
	if (started)
	{
		
	}
}

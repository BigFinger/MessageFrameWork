#define _CRT_SECURE_NO_WARNINGS
#include "Thread\Thread.h"
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

Thread::Thread(Runnable* task, const char* szThreadName = NULL){
	this->task = task;
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

bool Thread::start(){
	if (!started)
	{
		this->threadHandle = (HANDLE)_beginthreadex(NULL, 0, Thread::runCallback, this, 0, &threadId);
	}
	started = true;
	return started;
}

void Thread::join(){
	if (!this->started)
	{
		return;
	}
	if (!this->joined)
	{
		unsigned rv = WaitForSingleObject(this->threadHandle, INFINITE);
		CloseHandle(this->threadHandle);
		this->threadHandle = NULL;
		if (rv == WAIT_OBJECT_0 || rv == WAIT_ABANDONED)
		{
			printf("Failed to Join the Thread.\n");
		}
	}
	this->joined = true;
}

void Thread::sleep(int millisecs){
	Sleep(millisecs);
}

unsigned __stdcall Thread::runCallback(void *param){
	Thread* pThread = (Thread*)param;
	pThread->task->run();
	_endthreadex(0);
	return 0;
}

unsigned long Thread::getThreadId(){
	return threadId;
}

void Thread::setThreadName(char * str){
	if (str != NULL && str[0] != 0)
	{
		strncpy(mThreadName, str, 31);
		mThreadName[31] = 0;
	}
}

const char* Thread::getThreadName(){
	return mThreadName;
}

HANDLE Thread::getThreadHandle(){
	return this->threadHandle;
}


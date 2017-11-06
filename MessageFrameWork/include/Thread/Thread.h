#pragma once
#include "Runnable.h"
#include <windows.h>


typedef void* HANDLE;

class _declspec(dllexport) Thread: public Runnable {
private:
	Runnable *task;
	HANDLE threadHandle;
	unsigned int threadId;
	bool started;
	bool joined;
protected:
	char mThreadName[32];
public:
	void setThreadName(char* str);
	const char* getThreadName();
	unsigned long getThreadId();
	static unsigned long getCurrentThreadId();
public:
	static void sleep(int millsecs);
	static unsigned _stdcall runCallback(void *param);
public:
	Thread(const char* szThreadName = NULL);
	Thread(Runnable* task, const char* szThreadName = NULL);
	virtual ~Thread();
	virtual bool start();
	virtual void join();
	virtual HANDLE getThreadHandle();
protected:
	virtual void run(){};	
};
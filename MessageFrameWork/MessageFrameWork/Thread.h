#pragma once
#include "Runnable.h"
#include <windows.h>

typedef void* HANDLE;

class Thread: public Runnable {
private:
	Runnable *task;
	HANDLE threadHandle;
	unsigned int threadId;
	bool started;
	bool joined;
protected:
	char mThreadName[32];
public:
	static bool setThreadName(const char *str);
	static int getThreadName(char *buf, int len);
	static unsigned long getCurrentThreadId();
	static void sleep(int millsecs);
	static unsigned _stdcall runCallback(void *param);
public:
	Thread(const char* szThreadName = NULL);
	virtual ~Thread();
	virtual void start();
	virtual void join();
	virtual HANDLE getThreadHandle();
public:
	const char* getThreadName();
	unsigned long getThreadId();
protected:
	virtual void run(){};	
};
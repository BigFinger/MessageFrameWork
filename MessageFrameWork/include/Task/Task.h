#pragma once

#include "Thread/Runnable.h"
#include "TaskObserver.h"
#include "TaskRunner.h"


class Thread;
class MessageHandler;
class _declspec(dllexport) Task: public Runnable {
public:
	Task(TaskObserver& ob, const char* ThreadName);
	~Task();
public:
	bool start(TaskRunner* runner);
	bool isRunning() const;
public:
	void run();
private:
	void notifyObserver(int result);
private:
	friend class TaskHandler;
private:
	TaskObserver&	mObserver;
	TaskRunner*		mRunner;
	Thread*			mTaskThread;
	MessageHandler* mHandler;
	char			mThreadName[64];
	bool			mIsRunning;
};
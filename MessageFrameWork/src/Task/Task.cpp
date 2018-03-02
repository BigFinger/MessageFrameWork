#pragma once

#include "Task/Task.h"
#include "Thread/Thread.h"
#include "Handler/TaskHandler.h"
#include "Thread/MessageThread.h"

Task::Task(TaskObserver& ob, const char* threadName):mObserver(ob) {
	mHandler = new TaskHandler(this);
	mRunner = NULL;
	mIsRunning = false;
	mTaskThread = NULL;
	if (threadName != NULL)
	{
		strncpy(mThreadName, threadName, 63);
	}
	else
	{
		mThreadName[0] = 0;
	}
}

Task::~Task() {
	delete mHandler;
	mHandler = NULL;
	if (mTaskThread != NULL)
	{
		mTaskThread->join();
		delete mTaskThread;
		mTaskThread = NULL;
	}
}

bool Task::start(TaskRunner* taskRunner){
	if (taskRunner == NULL || mHandler->getLooper() == NULL || mIsRunning)
	{
		return false;
	}
	mRunner = taskRunner;
	mTaskThread = new Thread(this, mThreadName);
	if (!mTaskThread->start())
	{
		delete mTaskThread;
		mTaskThread = NULL;
		return false;
	}
	mIsRunning = true;
	return true;
}

bool Task::isRunning() const{
    return mIsRunning;
}

void Task::run(){
	int ret = mRunner->taskRun();
	Message* msg = mHandler->obtainMessage(ret);
	msg->sendToTarget();
}

void Task::notifyObserver(int result){
	mIsRunning = false;
	mObserver.taskFinished(result);
}

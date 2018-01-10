#pragma once
#include "MessageHandler.h"

class Task;
class TaskHandler: public MessageHandler {
public:
	TaskHandler (Task* task);
	~TaskHandler();
public:
	void handleMessage(Message &msg) const;

private:
	Task*	mTask;
};
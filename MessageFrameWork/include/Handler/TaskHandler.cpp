#pragma once

#include "Handler/TaskHandler.h"
#include "Task/Task.h"

TaskHandler::TaskHandler(Task* task):mTask(task){}

TaskHandler::~TaskHandler(){}

void TaskHandler::handleMessage(Message& msg) const {
	mTask->notifyObserver(msg.what);
}
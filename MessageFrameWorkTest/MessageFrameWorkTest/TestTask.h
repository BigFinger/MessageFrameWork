#pragma once
#include "Task/Task.h"
#include "Task/TaskObserver.h"
#include "Task/TaskRunner.h"
#include "ResultDefine.h"

class TestTask: public TaskRunner, public TaskObserver{
public:
    TestTask();
    ~TestTask();
public:
    void start();
    int taskRun();
    void taskFinished(int result);
private:
    Task* mTask;
};
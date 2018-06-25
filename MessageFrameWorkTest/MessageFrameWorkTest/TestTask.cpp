#include "TestTask.h"
#include "ResultDefine.h"

extern bool waitting;

TestTask::TestTask(){
    mTask = NULL;
}

TestTask::~TestTask(){
    if (mTask != NULL)
    {
        delete mTask;
    }
}

void TestTask::start(){
    
    if (mTask != NULL)
    {
        if (mTask->isRunning())
        {
            return;
        }
        delete mTask;
        mTask = NULL;
    }
    mTask = new Task(*this, "TestTask");
    if (mTask != NULL)
    {
        mTask->start((TaskRunner*)this);
    }
}

int TestTask::taskRun(){
    printf("Running the task\n");
    return (ResultState)HandleRequestSuccess;
}

void TestTask::taskFinished(int result){
    printf("Hey, Sir. This is your tea");
    waitting = false;
}
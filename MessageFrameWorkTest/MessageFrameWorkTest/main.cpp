#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Test/TestThread.h"
#include "TestTask.h"

bool waitting = false;

int main()
{
	TestThread* thread = new TestThread();
	thread->start();
	printf("Bad Boy: Look, There are many pretty girls in 85C!!!\n");
	MessageHandler* handler = thread->getHandler();
	Message* msg = handler->obtainMessage(HandleCoffee);
	msg->sendToTargetDelayed(1000);
	waitting = true;
	printf("Bad Boy is picking up pretty girls...\n");
	while(waitting)
	{
	}
    waitting = true;
    TestTask* task = new TestTask();
    task->start();
    while (waitting)
    {
    }
	msg = handler->obtainMessage(MESSAGE_ID_INTERNAL_EXIT);
	msg->postToTarget();
	system("PAUSE");
	return 0;
}
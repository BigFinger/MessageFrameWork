#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Test/TestThread.h"

bool waitting = false;

int main()
{
	TestThread* thread = new TestThread();
	thread->start();
	printf("Bad Boy: Look, There are many pretty girls in 85C!!!\n");
	MessageHandler* handler = thread->getHandler();
	Message* msg = handler->obtainMessage(HandleCoffee);
	msg->postToTarget();
	waitting = true;
	printf("Bad Boy is picking up pretty girls...\n");
	while(waitting)
	{
	}
	msg = handler->obtainMessage(MESSAGE_ID_INTERNAL_EXIT);
	msg->postToTarget();
	getchar();
}
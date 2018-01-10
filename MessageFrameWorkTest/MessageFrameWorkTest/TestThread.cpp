#include "TestThread.h"
#include "Message/Message.h"

extern bool waitting;

TestThread::TestThread():MessageThread("TestThread"){}

void TestThread::onInit(){
	mWorkStatus = "Free";
}

TestThread::~TestThread(){}

int TestThread::onMessage(Message& message){
	switch(message.what)
	{
	case HandleTea:
		{
			mWorkStatus = "Tea";
			printf("Handle the %s....\n", mWorkStatus.c_str());
			break;
		}
	case HandleMilk:
		{
			mWorkStatus = "Milk";
			printf("Handle the %s....\n", mWorkStatus.c_str());
			break;
		}
	case HandleCoffee:
		{
			mWorkStatus = "Coffee";
			printf("Handle the %s....\n", mWorkStatus.c_str());
			break;
		}
	case HandleBread:
		{
			mWorkStatus = "Bread";
			printf("Handle the %s....\n", mWorkStatus.c_str());
			break;
		}
	case HandleCake:
		{
			mWorkStatus = "Cake";
			printf("Handle the %s....\n", mWorkStatus.c_str());
			break;
		}
	default:
		break;
	}
	waitting = false;
	return 0;
}

void TestThread::onDestroy(){
	mWorkStatus = "Free";
}
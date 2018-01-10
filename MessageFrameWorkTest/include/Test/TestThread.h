#pragma once
#include "Thread/MessageThread.h"
#include  <string>

enum TestMessageId
{
	HandleTea = 0,
	HandleCoffee,
	HandleMilk,
	HandleBread,
	HandleCake,
};

class TestThread:public MessageThread{
public:
	TestThread();
	~TestThread();
public:
	int onMessage(Message& message);
	void onDestroy();
	void onInit();
private:
	string mWorkStatus;
};
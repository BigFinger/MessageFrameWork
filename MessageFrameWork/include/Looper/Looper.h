#pragma once
#include "BaseMessageLooper.h"
#include "Message/MessageQueue.h"
#include "Message/Message.h"

class Looper : public BaseMessageLooper{
private:
	MessageQueue<Message>* mQueue;
public:
	Looper();
	~Looper();
public:
	void loop();
private:
	void postMessage(Message* message);
private:
	static void initTLSKey();
};
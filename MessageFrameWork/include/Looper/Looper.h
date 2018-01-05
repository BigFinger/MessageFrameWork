#pragma once
#include "BaseMessageLooper.h"
#include "Message/Queue.h"
#include "Message/Message.h"

class _declspec(dllexport) Looper : public BaseMessageLooper{
private:
	Queue<Message>* mQueue;
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
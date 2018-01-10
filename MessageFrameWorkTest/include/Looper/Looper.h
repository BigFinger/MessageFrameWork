#pragma once
#include "BaseMessageLooper.h"
#include "Message/MessageQueue.h"
#include "Message/Message.h"

class _declspec(dllexport) Looper : public BaseMessageLooper{
private:
	MessageQueue* mQueue;
public:
	Looper();
	~Looper();
public:
	void loop();

private:
	void postMessage(Message* message, int when);
private:
	static void initTLSKey();
};
#pragma once
#include "BaseMessageLooper.h"

class Message;
class MessageQueue;
class Looper : public BaseMessageLooper{
private:
	MessageQueue* mQueue;
private:
	static Looper* prepare();
	static void destroy();
public:
	Looper();
	~Looper();
public:
	void loop();
	void removeMsgByID(int msgid);
private:
	void postMessage(Message* message, unsigned long when);

};
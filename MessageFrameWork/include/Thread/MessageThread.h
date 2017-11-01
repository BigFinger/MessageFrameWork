#pragma once
#include "Thread.h"
#include "Handler/MessageHandler.h"

class MessageHandler;
class Message;

class _declspec(dllexport) MessageThread: public Thread{
public:
	MessageThread(const char *szThreadName);
	~MessageThread();
public:
	void run();
public:
	virtual void onInit() = 0;
	virtual int onMessage(Message& message) = 0;
	virtual void onDestroy() = 0;
public:
	MessageHandler* getHandler();
	bool start();
	void quit(bool wait=true);
private:
	MessageHandler* mHandler;
};
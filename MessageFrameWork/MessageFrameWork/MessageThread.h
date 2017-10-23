#pragma once
#include "Thread.h"
#include "MessageHandler.h"

class MessageHandler;
class Message;

class MessageThreadHandler:public MessageHandler{
private:
	MessageThread *mThread;
public:
	MessageThreadHandler(MessageThread* thread, IMessageLooper* looper):MessageHandler(looper), mThread(thread){}
};

class MessageThread: public Thread{
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
	void start();
	void quit(bool wait=true);
private:
	MessageHandler* mHandler;
	char mThreadName[32];
};
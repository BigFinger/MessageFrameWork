#pragma once
#include "MessageHandler.h"
#include "Thread/MessageThread.h"

class MessageThreadHandler:public MessageHandler{
private:
	MessageThread *mThread;
public:
	MessageThreadHandler(MessageThread* thread, IMessageLooper* looper):MessageHandler(looper), mThread(thread){}
	void handleMessage(Message& message)const {
		mThread->onMessage(message);
	}
};
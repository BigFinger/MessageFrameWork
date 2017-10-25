#pragma once
#include "MessageHandler.h"
#include "MessageThread.h"

class MessageThreadHandler:public MessageHandler{
private:
	MessageThread *mThread;
public:
	MessageThreadHandler(MessageThread* thread, IMessageLooper* looper):MessageHandler(looper), mThread(thread){}
	void handlerMessage(Message& msg) const {
		mThread->onMessage(msg);
	}
};
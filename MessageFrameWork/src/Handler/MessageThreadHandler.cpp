#pragma once
#include "Handler/MessageHandler.h"
#include "Thread/MessageThread.h"
#include "Looper/Looper.h"

class MessageThreadHandler : public MessageHandler {
public:
	MessageThreadHandler(MessageThread* thread, Looper* looper) : MessageHandler(looper) {
		mThread = thread;
	}

public:
	void handleMessage(Message& message) const {
		if (message.what == MESSAGE_ID_INTERNAL_EXIT) {
			mLooper->quit();
		} else {
			mThread->onMessage(message);
		}
	}

private:
	MessageThread* mThread;
};
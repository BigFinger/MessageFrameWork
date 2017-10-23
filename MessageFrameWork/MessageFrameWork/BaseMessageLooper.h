#pragma once
#include "IMessageLooper.h"

class MessageHandler;
class BaseMessageLooper : public IMessageLooper {
protected:
	bool mQuitting;
	MessageHandler* mHandler;
public:
	BaseMessageLooper();
	~BaseMessageLooper();
	bool onProcMessage(Message* msg);
	void quit();
	MessageHandler* getHandler();
};
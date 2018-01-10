#pragma once
#include "Message/Message.h"

class Looper;
class IMessageLooper;
class _declspec(dllexport) MessageHandler {
protected:
	IMessageLooper* mLooper;
public:
	MessageHandler();
	MessageHandler(IMessageLooper* looper):mLooper(looper){}
	virtual ~MessageHandler();

	IMessageLooper* getLooper();
public:
	Message* obtainMessage();
	Message* obtainMessage(int what);
	void sendMessage(Message* msg, MessageControl* pControl = NULL);
	void sendDelayedMessage(Message* msg, unsigned long delayedMillis, MessageControl* pControl = NULL);
	void post(Runnable* r, MessageControl* pControl = NULL);
	void postDelayed(Runnable* r, unsigned long delayMillis, MessageControl* pControl = NULL);
public:
	virtual void handleMessage(Message& message) const;
};
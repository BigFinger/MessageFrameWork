#pragma once
#include "Message/Message.h"

class Looper;
class IMessageLooper;
class _declspec(dllexport) MessageHandler {
protected:
	IMessageLooper* mLooper;
public:
	MessageHandler();
	MessageHandler(IMessageLooper* looper):mLooper(looper){;}
	virtual ~MessageHandler(){;}

	IMessageLooper* getLooper();
public:
	Message* obtainMessage();
	Message* obtainMessage(int what);
	void sendMessage(Message* msg);
public:
	virtual void handleMessage(Message& message)const;
};
#pragma once
#include "Message/Message.h"

class Looper;
class IMessageLooper;
class MessageHandler {
protected:
	IMessageLooper* mLooper;
public:
	MessageHandler();
	MessageHandler(IMessageLooper* looper):mLooper(looper){;}
	virtual ~MessageHandler(){;}

	IMessageLooper* getLooper(){ return mLooper;}
public:
	Message* obtainMessage();
	Message* obtainMessage(int what);
	void sendMessage(Message* msg);
	bool looperNotReady(){return !mLooper;}
public:
	virtual void handleMessage(Message& message)const{;}
};
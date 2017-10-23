#pragma once
#include "Message.h"

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
	void post(Runnable* r);
	void postDelayed(Runnable* r, unsigned long delayMillis);
	void postAtTime(Runnable* r, unsigned long uptimeMillis);
	bool removeCallback(Runnable* r);
	bool removeCallbackWithCallback(Runnable* r);
	void postAndMerge(Runnable* r);
	void sendMessage(Message* msg);
	void sendMessageDelayed(Message* msg, unsigned long delayMillis);
	void sendMessageAtTime(Message* msg, unsigned long uptimeMillis);
	void removeMessage(int MsgID);
	bool looperNotReady(){return !mLooper;}
};
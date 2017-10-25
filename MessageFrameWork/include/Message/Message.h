#pragma once
#include<iostream>

class Runnable;
class MessageHandler;
class MessageQueue;
class BaseMessageLooper;

class Message{
public:
	int what;
	int result;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
	void* ptr;
	Runnable* callback;
	MessageHandler* target;
	unsigned long when;
	Message *next;

public:
	void postToTarget(MessageHandler* handle = NULL);
	void sendToTarget(MessageHandler* handle = NULL);
	void recycle();
	static void releasePool();
private:
	static Message* get();
	static Message* get(Runnable* r);
	static Message* get(MessageHandler* handler);

private:
	Message():what(0), target(NULL){init();}
	void init(){
		arg1 = arg2 = arg3 = arg4 = 0;
		ptr = NULL;
		result = 0;
		when = 0;
		callback = NULL;
	}
};
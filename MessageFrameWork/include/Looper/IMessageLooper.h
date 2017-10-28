#pragma once
class Message;
class MessageHandler;
class IMessageLooper{
public:
	virtual ~IMessageLooper(){}
	virtual void loop() = 0;
	virtual void quit() = 0;
	virtual bool onProcMessage(Message* msg) = 0;
	virtual void postMessage(Message* message) = 0;
public:
	static IMessageLooper* getForThread();
	static void setForThread(const IMessageLooper* looper);
	
};
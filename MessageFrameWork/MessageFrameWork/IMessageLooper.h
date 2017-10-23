#pragma once
class Message;
class MessageHandler;
class IMessageLooper {
public:
	static 
	static void setForThread(const IMessageLooper* looper);
public:
	virtual ~IMessageLooper(){}
	virtual void loop() = 0;
	virtual void quit() = 0;
	virtual bool onProcMessage(Message* msg) = 0;
	virtual void postMessage(Message* message, unsigned long when) = 0;
	virtual void removeMsgByID(int msgid) = 0;
	virtual MessageHandler* getHandler() = 0;
	virtual IMessageLooper* getForThread() = 0;
};
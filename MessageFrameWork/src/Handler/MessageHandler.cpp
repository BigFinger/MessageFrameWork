#include "Handler/MessageHandler.h"
#include "Looper/IMessageLooper.h"
#include "Message/Message.h"
#include "Thread/Runnable.h"

MessageHandler::MessageHandler(){
	mLooper = IMessageLooper::getForThread();
}

MessageHandler::~MessageHandler(){

}

Message* MessageHandler::obtainMessage(){
	Message *msg = Message::get();
	msg->target = this;
	return msg;
}

Message* MessageHandler::obtainMessage(int what){
	printf("Bad Boy: Hey waiter, Please Give me some Coffee!\n");
	Message* msg = Message::get();
	msg->what = what;
	msg->target = this;
	return msg;
}

IMessageLooper* MessageHandler::getLooper(){
	return mLooper;
}

void MessageHandler::handleMessage(Message& message) const {

}

void MessageHandler::sendMessage(Message* msg, MessageControl* pControl){
	if (mLooper != NULL)
	{
		if (pControl != NULL)
		{
			*pControl = msg->getControl();
		}
		mLooper->postMessage(msg, 0);	
	}
}

void MessageHandler::sendDelayedMessage(Message* msg, unsigned long delayedMillis, MessageControl* pControl){
	if (mLooper != NULL)
	{
		if (pControl != NULL)
		{
			*pControl = msg->getControl();
		}
		unsigned long when = GetTickCount() + delayedMillis;
		mLooper->postMessage(msg, when);	
	}
}

void MessageHandler::post(Runnable* r, MessageControl* pControl /* = NULL */){
	Message* msg = Message::get(r);
	msg->what = MESSAGE_ID_INTERNAL_RUNNABLE;
	r->mControl = msg->mControl;
	sendMessage(msg, pControl);
}

void MessageHandler::postDelayed(Runnable* r, unsigned long delayMillis, MessageControl* pControl /* = NULL */){
	Message* msg = Message::get(r);
	msg->what = MESSAGE_ID_INTERNAL_RUNNABLE;
	r->mControl = msg->mControl;
	sendDelayedMessage(msg, delayMillis, pControl);
}
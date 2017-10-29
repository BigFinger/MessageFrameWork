#include "Handler/MessageHandler.h"
#include "Looper/IMessageLooper.h"
#include "Message/Message.h"

MessageHandler::MessageHandler(){
	mLooper = IMessageLooper::getForThread();
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

void MessageHandler::handleMessage(Message& message)const {

}

void MessageHandler::sendMessage(Message* msg){
	if (mLooper != NULL)
	{
		mLooper->postMessage(msg);	
	}
}
#include "Message/Message.h"
#include "Message/MessageQueue.h"
#include "Handler/MessageHandler.h"

static MessageQueue<Message> gFreeQueue;

Message::Message():what(0), target(NULL), next(NULL){init();}

Message::~Message(){
	what = 0;
	target = NULL;
	init();
}

void Message::init(){
	arg1 = arg2 = arg3 = arg4 = 0;
	ptr = NULL;
	result = 0;
	when = 0;
	callback = NULL;
}

Message* Message::get(){
	Message* msg = NULL;
	msg = gFreeQueue.pop();

	if (msg != NULL)
	{
		msg->init();
		msg->what = 0;
		msg->target = NULL;
		return msg;
	}
	else
	{
		msg = new Message();
	}
	return msg;
}

void Message::postToTarget(MessageHandler* handle){
	printf("Waiter: OK, please Hold on!\n");
	if (target != NULL)
	{
		target->sendMessage(this);
	}
}

void Message::sendToTarget(MessageHandler* handle){
	if (target != NULL)
	{
		target->sendMessage(this);
	}
}

void Message::recycle(){
	gFreeQueue.push(this);
	printf("Waiter: Hey Sir, Your Coffee is here, please taste it~~~\n");
}

void Message::releasePool(){
	Message* m;
	while (!gFreeQueue.isEmpty()) {
		m = gFreeQueue.pop();
		delete m;
	}
}
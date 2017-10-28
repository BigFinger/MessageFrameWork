#include <iostream>
#include "Looper\BaseMessageLooper.h"
#include "Handler\MessageHandler.h"
using namespace std;

BaseMessageLooper::BaseMessageLooper():mQuitting(false){
	mHandler = new MessageHandler(this);
}

BaseMessageLooper::~BaseMessageLooper(){
	if (mHandler != NULL)
	{
		delete mHandler;
		mHandler = NULL;
	}
}

bool BaseMessageLooper::onProcMessage(Message* msg){
	if (msg != NULL && msg->target != NULL)
	{
		msg->target->handleMessage(*msg);
	}
	msg->recycle();
}


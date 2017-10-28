#include <iostream>
#include <windows.h>
#include "Looper\BaseMessageLooper.h"
#include "Handler\MessageHandler.h"
using namespace std;

static unsigned int gTLSKey = 0;

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
	if (msg->what == MESSAGE_ID_INTERNAL_EXIT)
	{
		mQuitting = true;
		msg->recycle();
		return false;
	}

	if (msg != NULL && msg->target != NULL)
	{
		msg->target->handleMessage(*msg);
	}
	msg->recycle();
	return true;
}

void BaseMessageLooper::quit(){
	Message* msg = Message::get();
	msg->what = MESSAGE_ID_INTERNAL_EXIT;
	postMessage(msg);
}

IMessageLooper* IMessageLooper::getForThread() {
	return (IMessageLooper*)TlsGetValue(gTLSKey);
}

void IMessageLooper::setForThread(const IMessageLooper* looper) {
	IMessageLooper* old = IMessageLooper::getForThread();

	if (old == looper) return;

	TlsSetValue(gTLSKey, (LPVOID)looper);

	delete old;
}

static void initTLSKey(){
	gTLSKey = TlsAlloc();
}
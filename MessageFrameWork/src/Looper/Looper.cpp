#include <iostream>
#include "Looper/Looper.h"

Looper::Looper(){
	mQuitting = false;
	mQueue = new Queue<Message>();
}

Looper::~Looper(){
	delete mQueue;
	mQueue = NULL;
}

void Looper::loop(){
	for(;;)
	{
		if (mQuitting)
		{
			break;
		}
		Message* msg = mQueue->pop();
		if (msg != NULL)
		{
			onProcMessage(msg);
		}
	}
}

void Looper::postMessage(Message * message){
	if (!mQuitting && mQueue != NULL)
	{
		mQueue->push(message);
	}
}

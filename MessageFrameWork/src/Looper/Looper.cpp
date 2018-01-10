#include <iostream>
#include "Looper/Looper.h"

Looper::Looper(){
	mQuitting = false;
	mQueue = new MessageQueue();
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
		Message* msg = mQueue->next();
		if (msg != NULL)
		{
			if (!onProcMessage(msg))
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
}

void Looper::postMessage(Message * message, int when){
	if (!mQuitting && mQueue != NULL)
	{
		mQueue->enqueueMessage(message, when);
	}
}

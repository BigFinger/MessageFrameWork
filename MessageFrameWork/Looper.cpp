#include <iostream>
#include "Looper/Looper.h"

Looper::Looper(){
	mQuitting = false;
	mQueue = new MessageQueue<Message>();
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
		if (msg == NULL)
		{

		}
	}
}

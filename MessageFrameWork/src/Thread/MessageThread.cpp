#include "Thread/MessageThread.h"

MessageThread::MessageThread(const char *szThreadName):Thread(szThreadName){
	mHandler = NULL;
}

MessageThread::~MessageThread(){
	delete mHandler;
}

void MessageThread::run(){
	IMessageLooper* looper = mHandler->getLooper();
	onInit();
	looper->loop();
	onDestroy();
}
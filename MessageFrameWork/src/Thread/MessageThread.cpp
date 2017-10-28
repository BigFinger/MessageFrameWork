#include "Thread/MessageThread.h"
#include "Looper/Looper.h"
#include "Handler/MessageThreadHandler.h"

MessageThread::MessageThread(const char *szThreadName):Thread(szThreadName){
	mHandler = NULL;
}

MessageThread::~MessageThread(){
	delete mHandler;
}

void MessageThread::run(){
	IMessageLooper* looper = mHandler->getLooper();
	IMessageLooper::setForThread(looper);
	onInit();
	looper->loop();
	onDestroy();
}

MessageHandler* MessageThread::getHandler(){
	return mHandler;
}

void MessageThread::start(){
	printf("Waiter: Hello, EveryBody, The 85C is opening~~~\n");
	Looper *looper = new Looper();
	mHandler = new MessageThreadHandler(this, looper);
	Thread::start();

}

void MessageThread::quit(bool wait) {
    MessageHandler* handler = getHandler();
    if (handler) {
        handler->obtainMessage(MESSAGE_ID_INTERNAL_EXIT)->postToTarget();
        /*
        等待消息线程退
        */
        if (wait && GetCurrentThreadId() != getThreadId())
            this->join();
    }
}
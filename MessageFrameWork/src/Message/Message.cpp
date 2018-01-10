#include "Message/Message.h"
#include "Storge/Queue.h"
#include "Handler/MessageHandler.h"

static Queue<Message> gFreeQueue;

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
    mControl = NULL;
}

MessageControl& Message::getControl(){
    if (mControl == NULL)
    {
        mControl = new MessageControl();
    }
    return *mControl;
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

Message* Message::get(Runnable* r){
    if (r == NULL)
    {
        return NULL;
    }
    Message* msg = get();
    msg->callback = r;
    return msg;
}

Message* Message::get(MessageHandler* handler){
    if (handler == NULL)
    {
        return NULL;
    }
    Message* msg = get();
    msg->target = handler;
    return msg;
}

void Message::postToTarget(MessageControl* pControl){
    printf("Waiter: OK, please Hold on!\n");
    if (target != NULL)
    {
        target->sendMessage(this, pControl);
    }
}

void Message::sendToTarget(MessageControl* pControl){
    if (target != NULL)
    {
        target->sendMessage(this, pControl);
    }
}

void Message::postToTargetDelayed(Runnable* r, unsigned long delayMillis, MessageControl* pControl){
	if (target != NULL)
	{
		target->postDelayed(r, delayMillis, pControl);
	}
}
void Message::sendToTargetDelayed(unsigned long delayMillis, MessageControl* pControl){
	if (target != NULL)
	{
		target->sendDelayedMessage(this, delayMillis, pControl);
	}
}

void Message::recycle(){
    gFreeQueue.push(this);
    printf("Waiter: Hey Sir, Your Coffee is here, please taste it~~~\n");
}

void Message::releasePool(){
    Message* m;
    while (!gFreeQueue.isEmpty()) 
	{
        m = gFreeQueue.pop();
        delete m;
    }
}

int Message::enterInProgressState(){
	int res = 0;
	if (mControl != NULL)
	{
		res = mControl->setInProcess() >= 0 ? 0 : -1;
	}
	return res;
}

int Message::enterCompleteState(){
	int res = 0;
	if (mControl != NULL)
	{
		res = mControl->setComplete() >= 0 ? 0 : -1;
	}
	return res;
}

bool Message::isNeedCallOnCancel(){
	if (mControl != NULL && callback != NULL)
	{
		return mControl->isNeedCallOnCancel();
	}
	return false;
}
#include "windows.h"
#include "Message/MessageQueue.h"

MessageQueue::MessageQueue():mFlag(FLAG_EMPTY), mCurrNumber(1){}

MessageQueue::~MessageQueue(){}

Message* MessageQueue::next(){
    while(true)
    {
        Message* msg = fetchNext();
        if (isMessageCanceled(msg))
        {
            msg->recycle();
        }
        else
        {
            return msg;
        }
    }
}

void MessageQueue::enqueueMessage(Message* message, unsigned long when){
    if (message != NULL)
    {
        message->when = when;
        message->mNumber = (unsigned int)InterlockedExchangeAdd((LONG*)&mCurrNumber, 1);
        if (when == 0)
        {
            mQueue.push(message);
        }
        else
        {

        }
    }
}

void MessageQueue::removeMsgByID(int msgid){

}


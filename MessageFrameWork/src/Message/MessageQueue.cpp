#include "windows.h"
#include "Message/MessageQueue.h"
#include "Lock/LockWrap.h"
#include "Lock/Mutex.h"


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
            do
            {
                LockWrap<Mutex> lock(mTimerHeapLock);
                mTimerHeap.push(when, message);
            }while(0);
        }
    }
    wakeupConsumer();
}

void MessageQueue::removeMsgByID(int msgid){
    mMapLock.lock();
    mCancelMap[msgid] = mCurrNumber;
    mMapLock.unlock();
}

void MessageQueue::wakeupConsumer(){
    if (FLAG_EMPTY == InterlockedCompareExchange((unsigned int*)&mFlag, FLAG_NOT_EMPTY, FLAG_EMPTY))
    {
        LockWrap<Mutex> lock(mWaitLock);
        mFlag = FLAG_NOT_EMPTY;
        mWaitLock.notify();
    }
}

unsigned int MessageQueue::getMsgCancleNo(int msgid){
    unsigned int res = 0;
    mMapLock.lock();
    std::map<int, unsigned int>::iterator iter = mCancelMap.find(msgid);
    if (iter != mCancelMap.end())
    {
        res = iter->second;
    }
    return res;
}

bool MessageQueue::isMessageCanceled(Message* msg){
    if (msg == NULL)
    {
        return true;
    }
    if (msg->what <= MESSAGE_ID_INTERNAL_EXIT)
    {
        return false;
    }
    unsigned int number = getMsgCancleNo(msg->what);
    if (number > msg->mNumber)
    {
        return true;
    }
    return false;
}

Message* MessageQueue::fetchNext(){
    unsigned int nextPollTimeOut = 0;
    while(true)
    {
        Message *msg = NULL;
        nextPollTimeOut = INFINITE;
        if (!mTimerHeap.isEmpty())
        {
            unsigned long timeNow = GetTickCount();
            LockWrap<Mutex> lock(mTimerHeapLock);
            __int64 when;
            while(mTimerHeap.top(&when))
            {
                int diff = (int)(timeNow - (unsigned long)when);
                if (diff >= 0)
                {
                    Message* msgTemp = (Message*)mTimerHeap.pop(NULL);
                    if (msgTemp != NULL)
                    {
                        return msgTemp;
                    }
                }
                else
                {
                    nextPollTimeOut = -diff;
					break;
                }
            }
        }
		if (mQueue.top() != NULL)
		{
			LockWrap<Mutex> lock(mQueueLock);
			msg = mQueue.pop();
			return msg;
		}
		if (FLAG_EMPTY == InterlockedCompareExchange((unsigned int*)&mFlag, FLAG_EMPTY, FLAG_NOT_EMPTY))
		{
			LockWrap<Mutex> lock(mWaitLock);
			if (mFlag == FLAG_NOT_EMPTY)
			{
				continue;
			}
			mWaitLock.wait(nextPollTimeOut);
		}
    }
	return NULL;
}


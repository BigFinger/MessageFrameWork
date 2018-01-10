#pragma once
#include <map>
#include "Message/Message.h"
#include "Storge/Queue.h"
#include "Storge/MinHeap.h"
#include "Lock/Mutex.h"
#include "Lock/SpinLock.h"

enum{FLAG_EMPTY, FLAG_NOT_EMPTY};

class Message;

class _declspec(dllexport) MessageQueue{
public:
    MessageQueue();
    ~MessageQueue();
public:
    Message* next();
    void enqueueMessage(Message* message, unsigned long when);
    void removeMsgByID(int msgid);
private:
    void wakeupConsumer();
    unsigned int getMsgCancleNo(int msgid);
    bool isMessageCanceled(Message* msg);
    Message* fetchNext();
private:
    Queue<Message> mQueue;
    MinHeap mTimerHeap;
    Mutex mQueueLock;
    Mutex mTimerHeapLock;
	Mutex mWaitLock;
    SpinLock mMapLock;
    volatile int mFlag;
    volatile unsigned int mCurrNumber;
    std::map<int, unsigned int> mCancelMap;
};
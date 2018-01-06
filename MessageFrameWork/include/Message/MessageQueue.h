#pragma once
#include <map>
#include "Message/Message.h"
#include "Storge/Queue.h"
#include "Storge/MinHeap.h"

enum{FLAG_EMPTY, FLAG_NOT_EMPTY};

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
    volatile int mFlag;
    volatile unsigned int mCurrNumber;
    std::map<int, unsigned int> mCancelMap;
};
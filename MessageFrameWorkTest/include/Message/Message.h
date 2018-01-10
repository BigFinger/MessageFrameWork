#pragma once
#include<iostream>
#include "Message/MessageQueue.h"
#include "Message/MessageControl.h"

class Runnable;
class MessageHandler;
class BaseMessageLooper;
class MessageControl;

#define MSSSAGE_ID_INTERNAL_BASE  -0x1000
#define MESSAGE_ID_INTERNAL_EXIT  MSSSAGE_ID_INTERNAL_BASE-1
#define MESSAGE_ID_INTERNAL_TIMER MSSSAGE_ID_INTERNAL_BASE-2
#define MESSAGE_ID_INTERNAL_RUNNABLE MSSSAGE_ID_INTERNAL_BASE-3

class _declspec(dllexport) Message{
public:
    void postToTarget(MessageControl* pControl = NULL);
    void sendToTarget(MessageControl* pControl = NULL);
	void postToTargetDelayed(Runnable* r, unsigned long delayMillis, MessageControl* pControl = NULL);
	void sendToTargetDelayed(unsigned long delayMillis, MessageControl* pControl = NULL);
    void recycle();
    static void releasePool();
private:
    static Message* get();
    static Message* get(Runnable* r);
    static Message* get(MessageHandler* handler);
private:
	int enterInProgressState();
	int enterCompleteState();
	bool isNeedCallOnCancel();
private:
    friend class MessageHandler;
    friend class BaseMessageLooper;
    friend class MessageQueue;
public:
	~Message();
private:
    Message();
    void init();
    MessageControl& getControl();
public:
    int what;
    int result;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    void* ptr;
    Runnable* callback;
    MessageHandler* target;
    unsigned long when;
    Message *next;
private:
    MessageControl* mControl;
    volatile unsigned int mNumber;
};
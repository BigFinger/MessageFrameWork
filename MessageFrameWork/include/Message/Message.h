#pragma once
#include<iostream>
#include "Message/MessageQueue.h"
#include "Message/MessageControl.h"

class Runnable;
class MessageHandler;
class BaseMessageLooper;

#define MESSAGE_ID_INTERNAL_EXIT   -0x1000

class _declspec(dllexport) Message{
public:
    void postToTarget(MessageHandler* handle = NULL);
    void sendToTarget(MessageHandler* handle = NULL);
    void recycle();
    static void releasePool();
private:
    static Message* get();
    static Message* get(Runnable* r);
    static Message* get(MessageHandler* handler);
private:
    friend class MessageHandler;
    friend class BaseMessageLooper;
    friend class MessageQueue;
private:
    Message();
    ~Message();
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
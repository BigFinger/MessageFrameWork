#pragma once
#include<iostream>
using namespace std;

class MessageControl;

class _declspec(dllexport) Runnable{
protected:
	Runnable();
public:
	virtual void run() = 0;
	virtual void onCancel(){};
	virtual ~Runnable(){}
private:
	bool cancel();
	bool cancelWithCallback();
private:
	friend class Message;
	friend class MessageHandler;
	MessageControl* mControl;
};
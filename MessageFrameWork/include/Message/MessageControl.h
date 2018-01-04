#pragma once
#include "Message.h"

class _declspec(dllexport) MessageControl{
public:
	MessageControl();
	bool cancel();
	bool cancelWithCallback();
	bool isComplete();
	bool isCanceled();
	bool isNeedCallOnCancel();

private:
	friend class Message;
	int setInProcess();
	int setComplete();
	int cancelInternal(bool bCallback);

private:
	enum
	{
		STATE_IN_QUEUE,
		STATE_IN_PROGRESS,
		STATE_COMPLETE,
		STATE_CANCELED,
		STATE_CANCEL_WITH_CALLBACK
	};
	~MessageControl();
	volatile unsigned int mFlag;
};
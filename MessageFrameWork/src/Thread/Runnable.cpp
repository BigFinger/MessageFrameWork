#include "Thread/Runnable.h"
#include "Message/MessageControl.h"
Runnable::Runnable(){}

bool Runnable::cancel(){
	bool res = false;
	if (mControl != NULL)
	{
		res = mControl->cancel();
	}
	return res;
}

bool Runnable::cancelWithCallback(){
	bool res = false;
	if (mControl != NULL)
	{
		res = mControl->cancelWithCallback();
	}
	return res;
}
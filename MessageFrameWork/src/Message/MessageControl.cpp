#include <windows.h>
#include "Message/MessageControl.h"

MessageControl::MessageControl():mFlag(STATE_IN_QUEUE){}

bool MessageControl::cancel(){
	return cancelInternal(false) != -1;
}

bool MessageControl::cancelWithCallback(){
	return cancelInternal(true) != -1;
}

int MessageControl::cancelInternal(bool bCallback){
	int result = 1;
	if (mFlag == STATE_CANCELED)
	{
		result = 0;
		return result;
	}
	/* mFlag��������������Ƚϣ�����ȣ�������λ�ڶ�������.����ֵΪmFlagԭ�ȵ�ֵ���ú�����֤�̻߳��� */
	int old = InterlockedCompareExchange(&mFlag, bCallback ? STATE_CANCEL_WITH_CALLBACK : STATE_CANCELED, STATE_IN_QUEUE);
	if (old == STATE_IN_PROGRESS)
	{
		result = -1;
	}
	else if (old == STATE_COMPLETE)
	{
		result = -2;
	}
	return result;
}

int MessageControl::setInProcess(){
	int result = -1;
	if (mFlag == STATE_IN_PROGRESS)
	{
		result = 0;
		return result;
	}
	int old = InterlockedCompareExchange(&mFlag, STATE_IN_PROGRESS, STATE_IN_QUEUE);
	if (old == STATE_IN_QUEUE)
	{
		result = 1;
	}
	else if (old == STATE_COMPLETE)
	{
		result = -2;
	}
	return result;
}

int MessageControl::setComplete(){
	int result = -1;
	if (mFlag == STATE_COMPLETE)
	{
		result = 0;
	}
	int old = InterlockedCompareExchange(&mFlag, STATE_COMPLETE, STATE_IN_PROGRESS);
	if (old == STATE_IN_PROGRESS)
	{
		result = 1;
	}
	else if (old == STATE_IN_QUEUE)
	{
		result = -2;
	}
	return result;
}
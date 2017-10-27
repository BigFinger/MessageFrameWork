#include "Message/MessageQueue.h"

template <class T>
MessageQueue<T>::MessageQueue():mHead(NULL),mTail(NULL),mLength(0){}

template <class T>
MessageQueue<T>::~MessageQueue(){
	while(mHead != mTail)
	{
		T* e = mHead;
		mHead = mHead->next;
		delete e;
		e = NULL;
	}
	delete mHead;
	mHead = NULL;
	mTail = NULL;
}

template <typename T>
void MessageQueue<T>::isEmpty(){
	if (mHead == mTail == NULL)
	{
		return true;
	}
	return false;
}

template <class T>
bool MessageQueue<T>::push(const T* &e){
	if (e != NULL)
	{
		if (mHead == NULL)
		{
			mHead = e;
			mTail = e;
		}
		else
		{
			mTail->next = e;
			mTail = e;
			e->next = NULL;
		}
		mLength++;
	}
	else
	{
		return false;
	}
}

template <class T>
T* MessageQueue<T>::pop(){
	T* e = NULL
	if (isEmpty())
	{
		return e;
	}
	else if (mHead == mTail)
	{
		e = mHead;
		mHead = NULL;
		mTail = NULL;
	}
	else
	{
		e = mHead;
		mHead = mHead->next;
		e->next = NULL;
	}
	mLength--;
	return e;
}
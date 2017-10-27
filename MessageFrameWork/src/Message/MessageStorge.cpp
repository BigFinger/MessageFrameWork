#include "Message/MessageStorge.h"

template <class T>
MessageStorge<T>::MessageStorge():mHead(NULL),mTail(NULL),mLength(0){}

template <class T>
MessageStorge<T>::~MessageStorge(){
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
void MessageStorge<T>::isEmpty(){
	if (mHead == mTail == NULL)
	{
		return true;
	}
	return false;
}

template <class T>
bool MessageStorge<T>::push(const T* &e){
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
T* MessageStorge<T>::pop(){
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
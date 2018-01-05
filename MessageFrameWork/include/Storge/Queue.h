#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Queue{
public:
	Queue();
	~Queue();
public:
	bool isEmpty();
	void push(T* const &e);
	T* pop();

private:
	T* mHead;
	T* mTail;
	unsigned int mLength;
};

template <class T>
Queue<T>::Queue():mHead(NULL),mTail(NULL),mLength(0){}

template <class T>
Queue<T>::~Queue(){
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
bool Queue<T>::isEmpty(){
	if (mHead == NULL && mTail == NULL)
	{
		return true;
	}
	return false;
}

template <class T>
void Queue<T>::push(T* const &e){
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
}

template <class T>
T* Queue<T>::pop(){
	T* e = NULL;
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
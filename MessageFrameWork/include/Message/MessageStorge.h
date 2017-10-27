#pragma once
#include <iostream>

template <typename T>
class MessageStorge{
public:
	MessageStorge();
	~MessageStorge();
public:
	bool isEmpty();
	bool push(const T* &e);
	T* pop();

private:
	volatile T* mHead;
	volatile T* mTail;
	unsigned int mLength;
};
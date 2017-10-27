#pragma once
#include <iostream>
#include <vector>

template <typename T>
class MessageQueue{
public:
	MessageQueue();
	~MessageQueue();
public:
	bool isEmpty();
	bool push(const T* &e);
	T* pop();

private:
	volatile T* mHead;
	volatile T* mTail;
	unsigned int mLength;
};
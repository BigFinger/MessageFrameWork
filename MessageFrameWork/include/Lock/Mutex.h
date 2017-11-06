#pragma once
#include "ISynchronizable.h"

class _declspec(dllexport) Mutex:public ISynchronizable {
public:
	Mutex();
	virtual ~Mutex();

public:
	virtual void lock();
	virtual void unlock();
	virtual void wait();
	virtual void wait(unsigned long millisecs);
	virtual void notify();
	virtual void notifyAll();

private:
	Mutex(const Mutex& mutex);
	Mutex& operator = (const Mutex& mutex);

private:
	ISynchronizable* mImpl;
};
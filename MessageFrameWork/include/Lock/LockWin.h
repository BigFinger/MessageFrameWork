#pragma once
#include <windows.h>
#include <map>
#include "ISynchronizable.h"

class LockWin : public ISynchronizable{
public:
	LockWin();
	virtual ~LockWin();
public:
	void lock();
	void unlock();
	void wait();
	void wait(unsigned long millisecs);
	void notify();
	void notifyAll();

private:
	void operator=(const LockWin& lock);
	LockWin(const LockWin& lock);
private:
	volatile unsigned int						_owner;
	volatile unsigned int						_count;
	CRITICAL_SECTION							_mutex;
	CONDITION_VARIABLE							_condition;
	std::map<unsigned int, unsigned int>		_count_before_wait;
};
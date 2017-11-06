#pragma once

class ISynchronizable{
public:
	virtual ~ISynchronizable();
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual void wait() = 0;
	virtual void wait(unsigned long millisecs) = 0;
	virtual void notify() = 0;
};
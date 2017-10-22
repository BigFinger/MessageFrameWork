#pragma once

class Runnable{
protected:
	Runnable();
public:
	virtual void run() = 0;
	virtual void onCancel() = 0;
	virtual ~Runnable(){}
};
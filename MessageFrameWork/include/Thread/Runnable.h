#pragma once
#include<iostream>
using namespace std;
class Runnable{
protected:
	Runnable();
public:
	virtual void run() = 0;
	virtual ~Runnable(){}
};
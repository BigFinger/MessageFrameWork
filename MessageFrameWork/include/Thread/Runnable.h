#pragma once
#include<iostream>
using namespace std;
class _declspec(dllexport) Runnable{
protected:
	Runnable();
public:
	virtual void run() = 0;
	virtual ~Runnable(){}
};
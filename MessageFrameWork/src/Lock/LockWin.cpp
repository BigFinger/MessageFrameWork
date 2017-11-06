#include <assert.h>
#include "Lock/LockWin.h"
#include "Thread/Thread.h"

LockWin::LockWin():_owner(0),_count(0) {
	SetLastError(0);
	InitializeCriticalSection(&_mutex);
	InitializeConditionVariable(&_condition);
}

LockWin::~LockWin(){
	DeleteCriticalSection(&_mutex);
}

void LockWin::lock(){
	if (Thread::getCurrentThreadId() == _owner)
	{
		_count++;
	}
	else
	{
		SetLastError(0);
		EnterCriticalSection(&_mutex);
		_count = 1;
		_owner = Thread::getCurrentThreadId();
	}
}

void LockWin::unlock(){
	if (_count > 0 && Thread::getCurrentThreadId() == _owner)
	{
		_count--;
	}
	if (_count == 0)
	{
		SetLastError(0);
		_owner = 0;
		LeaveCriticalSection(&_mutex);
	}
}

void LockWin::wait(){
	SetLastError(0);
	assert(Thread::getCurrentThreadId() == _owner);
	if (Thread::getCurrentThreadId() != _owner)
	{
		return;
	}
	_count_before_wait[Thread::getCurrentThreadId()] = _count;
	SleepConditionVariableCS(&_condition, &_mutex, 0XFFFFFFFF);
	_count = _count_before_wait[Thread::getCurrentThreadId()];
	_owner = Thread::getCurrentThreadId();
}

void LockWin::wait(unsigned long millisecs){
	SetLastError(0);
	assert(Thread::getCurrentThreadId() == _owner);
	if (Thread::getCurrentThreadId() != _owner)
	{
		return;
	}
	_count_before_wait[Thread::getCurrentThreadId()] = _count;
	if (SleepConditionVariableCS(&_condition, &_mutex, millisecs))
	{
		_count = _count_before_wait[Thread::getCurrentThreadId()];
		_owner = Thread::getCurrentThreadId();
	}
	else
	{
		_count = _count_before_wait[Thread::getCurrentThreadId()];
		_owner = Thread::getCurrentThreadId();
	}
	DWORD e = GetLastError();
}

void LockWin::notify(){
	SetLastError(0);
	WakeConditionVariable(&_condition);
}

void LockWin::notifyAll(){
	SetLastError(0);
	WakeAllConditionVariable(&_condition);
}
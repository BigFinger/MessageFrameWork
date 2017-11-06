#pragma once

template <class T>
class LockWrap{
public:
	LockWrap(T& Lock):mLock(&Lock){
		mLock->lock();
	}
	~LockWrap(){
		mLock->unlock();
	}
protected:
	T* mLock;
};
#include "Lock/SpinLock.h"

SpinLock::SpinLock(){
    InitializeCriticalSection(&mCriticalSection);
}

SpinLock::~SpinLock(){
    DeleteCriticalSection(&mCriticalSection);
};

void SpinLock::lock(){
    EnterCriticalSection(&mCriticalSection);
}

bool SpinLock::trylock(){
    return TRUE == TryEnterCriticalSection(&mCriticalSection);
}

void SpinLock::unlock(){
    LeaveCriticalSection(&mCriticalSection);
}
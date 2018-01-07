#pragma once
#include <windows.h>

class SpinLock{
public:
    SpinLock();
    ~SpinLock();
public:
    /* ������ */
    void lock();
    /* �������� */
    bool trylock();
    void unlock();
private:
    CRITICAL_SECTION mCriticalSection;
};
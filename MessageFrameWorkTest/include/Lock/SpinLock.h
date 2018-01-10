#pragma once
#include <windows.h>

class SpinLock{
public:
    SpinLock();
    ~SpinLock();
public:
    /* ×èÈûËø */
    void lock();
    /* ·Ç×èÈûËø */
    bool trylock();
    void unlock();
private:
    CRITICAL_SECTION mCriticalSection;
};
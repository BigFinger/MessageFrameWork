#pragma once
#include <windows.h>
#include <map>
#include "ISynchronizable.h"

class Lock : public ISynchronizable{
public:
    Lock();
    virtual ~Lock();
public:
    void lock();
    void unlock();
    void wait();
    void wait(unsigned long millisecs);
    void notify();
    void notifyAll();

private:
    void operator=(const Lock& lock){}
    Lock(const Lock& lock){}
private:
    volatile unsigned int                       _owner;
    volatile unsigned int                       _count;
    CRITICAL_SECTION                            _mutex;
    CONDITION_VARIABLE                          _condition;
    std::map<unsigned int, unsigned int>        _count_before_wait;
};
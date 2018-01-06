#include "Lock/Mutex.h"
#include "Lock/Lock.h"

Mutex::Mutex(){
    mImpl = new Lock();
}

Mutex::~Mutex(){
    if (mImpl)
    {
        delete mImpl;
    }
    mImpl = NULL;
}

void Mutex::lock(){
    mImpl->lock();
}

void Mutex::unlock(){
    mImpl->unlock();
}

void Mutex::wait(){
    mImpl->wait();
}

void Mutex::wait(unsigned long millisecs){
    if (INFINITE == millisecs)
    {
        mImpl->wait();
    }
    else
    {
        mImpl->wait(millisecs);
    }
}

void Mutex::notify() {
    mImpl->notify();
}

void Mutex::notifyAll() {
    mImpl->notifyAll();
}
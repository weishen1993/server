//@Author weishen
//mutex class

//#ifndef WEISHEN_BASE_MUTEX_H_
//#define WEISEHN_BASE_MUTEX_H_

#pragma once
#include <cstdio>
#include <pthread.h>
#include "noncopyable.h"

class MutexLock : noncopyable
{
public:
    MutexLock() { pthread_mutex_init(&mutex, NULL); }
    ~MutexLock() { pthread_mutex_destroy(&mutex); }

    void lock() { pthread_mutex_lock(&mutex); }
    void unlock() { pthread_mutex_unlock(&mutex); }
    pthread_mutex_t* get() { return &mutex; }

private:
    pthread_mutex_t mutex;

private:
    friend class Condition;
};

class MutexLockGuard : noncopyable 
{
public:
    explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex) { mutex_.lock(); }
    ~MutexLockGuard() { mutex_.unlock(); }

private:
    MutexLock& mutex_;
};

//#endif

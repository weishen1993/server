//@Author weishen
//condition class

//#ifndef WEISHEN_BASE_CONDITION_H_
//#define WEISHEN_BASE_CONDITION_H_

namespace weishen{
#pragma once
#include <error.h>
#include <pthread.h>
#include <time.h>
#include <cstdint>
#include "mutex.h"
#include "noncopyable.h"

class Condition : noncopyable
{
public:
    //explicit xian shi de 
    explicit Condition(MutexLock& mutex) : mutex_(mutex) 
    {
        pthread_cond_init(&cond_, NULL);
    }
    ~Condition() { pthread_cond_destroy(&cond_); }

    void wait() { pthread_cond_wait(&cond_,mutex_.get()); }
    void notify() { pthread_cond_signal(&cond_); }
    void notifyAll() { pthread_cond_broadcast(&cond_); }
    
    bool waitForSeconds(int seconds)
    {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond_,mutex_.get(),&abstime);
    }

private:
    MutexLock& mutex_;
    pthread_cond_t cond_;
};

}
//#endif

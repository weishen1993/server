#include <assert.h>
#include <stdio.h>
#include <string>
#include <pthread.h>
#include "ThreadPool.h"
#include <functional>
using namespace std;

ThreadPool::ThreadPool(const string& nameArg)
    :mutex_(),
    name_(nameArg),
    maxQueueSize_(0),
    running_(false)
{
    pthread_cond_init(&notEmpty_, NULL);
    pthread_cond_init(&notFull_,NULL);
}

ThreadPool::~ThreadPool()
{
    if (running_)
    {
        stop();
    }
}

void ThreadPool::start(int numThreads)
{
    assert(threads_.empty());
    running_ = true;
    threads_.reserve(numThreads);
    for(int i = 0; i < numThreads; ++i)
    {
        pthread_t pthreadId;
        if(0 != pthread_create(&pthreadId, NULL,std::bind(&ThreadPool::runInThread,this),NULL));
        {
            perror("pthread_create error\n");
        }

        threads_.emplace_back(pthreadId);
    }
}

void ThreadPool::stop()
{
    pthread_mutex_lock(&mutex_);
    running_ = false;
    pthread_cond_broadcast(&notEmpty_);
    pthread_mutex_unlock(&mutex_);

    for (auto& thr : threads_)
    {
        pthread_join(thr, NULL);
    }      
}

size_t ThreadPool::queueSize() const
{
  return queue_.size();
}

void ThreadPool::run(Task task)
{
    if(threads_.empty())
    {
        task();
    }
    else
    {
        pthread_mutex_lock(&mutex_);
        while (isFull())
        {
            pthread_cond_wait(&notFull_,&mutex_);
        }
        assert(!isFull());

        queue_.push_back(task);
        pthread_cond_signal(&notEmpty_);
        pthread_mutex_unlock(&mutex_);
    }
}

ThreadPool::Task ThreadPool::take()
{
    pthread_mutex_lock(&mutex_);
    while (queue_.empty() && running_)
    {
        pthread_cond_signal(&notEmpty_);
    }

    Task task;
    if (!queue_.empty())
    {
        task = queue_.front();
        queue_.pop_front();
        if(maxQueueSize_> 0)
        {
            pthread_cond_signal(&notFull_);
        }
    }

    return task;
}

bool ThreadPool::isFull() const
{
    return maxQueueSize_ > 0 && queue_.size() >= maxQueueSize_;
}

void* ThreadPool::runInThread()
{
    while(running_)
    {
        Task task(take());
        if(task)
        {
            task();
        }
    }
}


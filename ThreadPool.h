
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <string>
#include <pthread.h>
#include <deque>
#include <vector>

using namespace std;

//template <typename TYPE, void (TYPE::*runInThread)() >
//void* _thread_t(void* param)//线程启动函数，声明为模板函数
//{
// TYPE* This = (TYPE*)param;
// This->runInThread();
// return NULL;
// }



class ThreadPool
{
public:
    typedef void (*Task)();
    
    explicit ThreadPool(const string& nameArg = string("ThreadPool"));
    ~ThreadPool();

    void start(int numThreads);
    void stop();

    const string& name() const
    { return name_; }

    size_t queueSize() const;

    void run(Task f);

    void* runInThread();
private:
    bool isFull() const;
    //void* runInThread();
    Task take();

    pthread_mutex_t mutex_;
    pthread_cond_t notEmpty_;
    pthread_cond_t notFull_;
    string name_;
    std::vector<pthread_t> threads_;
    std::deque<Task> queue_;
    size_t maxQueueSize_;
    bool running_;
};

#endif

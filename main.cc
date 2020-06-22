#include <iostream>
#include "mutex.h"
#include "condition.h"
#include <pthread.h>
using namespace std;

int main()
{
    cout<<"hello"<<endl;
    {
        weishen::MutexLock  mutex;
        weishen::MutexLockGuard mymutex(mutex);
    }

    cout<<"world"<<endl;
    return 0;
}

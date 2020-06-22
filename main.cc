#include <iostream>
#include "mutex.h"
#include <pthread.h>
using namespace std;

int main()
{
    cout<<"hello"<<endl;
    {
        MutexLock  mutex;
        MutexLockGuard mymutex(mutex);
    }

    cout<<"world"<<endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int checkCPU()
{
    union w
    {
        int a;
        char b;
    }c;
    c.a = 1;
    return (c.b == 1);//小端返回1，大端返回0
}


int main()
{
    int flag= checkCPU();
    cout<<flag<<endl;
    return 0;
}

#include <thread>
#include <iostream>
using namespace std;

int add(int a, int b)
{
    return a + b;
}

int main()
{
    thread th(add, 3, 4);
    th.join();
    // run add function in a thread
    // pass 3 and 4 as arguments
    return 0;
}


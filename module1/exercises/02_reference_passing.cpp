#include <thread>
#include <iostream>
using namespace std;

void add10(int & a)
{
    a += 10;
    cout << "inside thread: " << a << '\n';
}

int main()
{
    // run add10 function in a thread
    // pass 5 as an argument and read it's value
    int a{5};
    thread th(add10, std::ref(a));
    cout << "before join: " << a << '\n';
    th.join();
    cout << "after join: " << a << '\n';
    return 0;
}


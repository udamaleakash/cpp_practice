// mutlithreding

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m1;
int counter = 0;


void increment()
{
    for (int i = 0; i < 100000; i++)
    {
        counter++;
    }

    cout << counter << endl;
}

int main()
{
    thread t1(increment);
    thread t2(increment);
    // t1.join(); // join() is used to wait for the thread to complete before main thread continues. It will block the main thread until the thread t1 completes its execution.
    // t2.join();
    t1.detach(); // detach() is used to run the thread in background and main thread will not wait for it to complete. It will run independently.
    t2.detach();
    return 0;
}
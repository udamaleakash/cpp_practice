#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;

mutex m;
int count = 0;
atomic<int> count = 0; // use atomic
void print(const char *str, int count)
{
    for (int i = 1; i <= count; i++)
    {
        // lock_guard<mutex>lock(m);
        // m.lock();
        cout << str << " " << i << endl;
        // m.unlock();
    }
}
void print1()
{
    for (int i = 0; i < 100000; i++)
    {
        // lock_guard<mutex> lock(m);
        count++;
    }
}

int main()
{
    // thread t1(print, " Flask", 5);
    // thread t2(print, " Python ", 5);

    // t1.join();
    // t2.join();
    // what is dead lock?
    // -> When two or more threads wait for each other's lock
    //  thread 1 lock A - wait for lock B
    //  thread 2 lock B - wait for lock A
    //  it programe frezzes.

    // what is race condition?
    // -> When multiple threads access shared data simultaneously and modify it - unperdicable result.
    // or
    // Two or more threads access shared data at the same time and at least one thread modifies it, leading to unpredictable results.
    // The final result depends on which thread runs first.
    // it show in below t3, t4, t5, t6 threads and prevent with use of lock_guard mutex or atomic variables
    // e.g
    thread t3(print1);
    thread t4(print1);
    thread t5(print1);
    thread t6(print1);
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    cout << "Thread t3 Count: " << count << endl;
    // these are ways to prevent wrong result while multithreading
    // 1. mutex      - m.lock() m.unlock()
    // 2. lock_guard - lock_guard<mutex>lock(m)
    // 3. atomic variable - atomic<int>count=0;

    // diff Race condition & Dead lock
    /* Race condition-> Threads run simultaneously,
    Wrong result, Example: count++ issue */
    /* Dead lock-> Threads wait forever, Program stuck, Happens due to improper locking, Example: two mutex locking */

    /* What is deadlock?

    Deadlock is a situation where two or more threads wait indefinitely for each other’s resources, causing the program to hang.

    How to prevent it?

    By maintaining consistent lock ordering, using std::lock or scoped_lock, minimizing nested locks, and breaking circular wait conditions.
    
    Always lock in same order
    Use std::lock()
    Use scoped_lock (C++17)
    std::scoped_lock lock(m1, m2);

    Is it same as race condition?

    No. Race condition leads to inconsistent results due to lack of synchronization, while deadlock causes threads to block indefinitely due to improper locking. */

    /* What is std::atomic?
    -> #include <atomic>
      atomic<int> counter(0);
      counter++; 
      better perfromnace for than mutex for simple variables
    */
   
    /* What happens if thread object is destroyed without join/detach?
    -> std::terminate() is called.  */

    cout << "This is End of Programmme." << endl;
    return 0;
}

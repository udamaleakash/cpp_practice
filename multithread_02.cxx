#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

void task()
{
    cout << "thread is running" << endl;
}

int count = 0, count2 = 10000;
mutex mtx;
void increment()
{
    for (int i = 0; i < 10000; i++)
    {
        mtx.lock(); // to avoid race condition
        count++;
        mtx.unlock();
    }
}
void decrement()
{
    for (int i = 10000; i > 0; i--)
    {
        lock_guard<mutex> lock(mtx); // auto lock / unlock
        count2--;
    }
}

queue<int> q;
mutex mtx2;
condition_variable cv;

void producer()
{
    /* Producer
       Locks the mutex
       Adds data to the queue
       Notifies consumer (notify_one())
       Unlocks mutex */

    for (int i = 1; i <= 5; i++)
    {
        unique_lock<mutex> lock(mtx2); // is used instead of lock_guard becasue it wroks with condi. variable, this ensure only one thread access the queue at a time.
        q.push(i);
        cout << "Produced: " << i << endl;
        cv.notify_one();
    }
}

void consumer()
{
    /* Consumer
      Locks the mutex
      If queue is empty → waits (cv.wait())
      When notified → wakes up
      Consumes data
      Unlocks mutex */

    for (int i = 1; i <= 5; i++)
    {
        unique_lock<mutex> lock(mtx2);
        cv.wait(lock, []
                { return !q.empty(); }); // condition variable lambda, explain in below

        cout << "Consumed: " << q.front() << endl;
        q.pop();
    }
    /* Waiting on condition variable
    if queue is empty then release lock & consumer cv it will wait (go to sleep state)
    when queue is not empty means producer adds data and call cv.notify_one() the consumer wakes up & check !q.empty() and print q.front() */
}
int main()
{
    thread t3(task);
    t3.join(); // join is manadtory otherwise program is termainate
    thread t4(increment);
    thread t5(increment);
    thread t6(increment); 
    t4.join();
    t5.join();
    t6.join();
    cout << "Increment: " << count << endl;

    // Race Condition:-> Multiple threads access the same data at the same time, and the result becomes unpredictable.
    // Improve mutex handling using RAII, means use use lock_guard
    thread t7(decrement);
    thread t8(decrement);
    thread t9(decrement);
    t7.join();
    t8.join();
    t9.join();
    cout << "Decrement: " << count2 << endl;

    /* Producer–Consumer Problem (Multithreading) */
    /* The Producer–Consumer problem is a classic synchronization problem where:
        A producer thread generates data and adds it to a shared buffer (like a queue).
        A consumer thread removes and processes that data.
        Both threads run concurrently, so we must ensure safe access to shared data.
    * Core Problem -->
        If the producer is too fast → buffer may overflow
        If the consumer is too fast → buffer may be empty
        Multiple threads accessing the same data can cause race conditions

    * One liner ->
        Producer generates data, consumer consumes it, and synchronization tools like mutex and condition variables ensure safe and efficient communication between threads.
    */

    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();

    /* What is Deadlock?
        Threads are waiting for each other forever → program freezes.

        A deadlock is a situation in multithreading where Two or more threads are waiting forever for each other to release resources, and none of them can proceed.

        What happens?
        thread1 locks m1 and waits for m2
        thread2 locks m2 and waits for m1
        Both are waiting → program stuck forever = Deadlock

        Real-Life Analogy
        Two people:
        Person A holds key 1, needs key 2
        Person B holds key 2, needs key 1
        Both wait forever
    */

    /* Race condition :- multiple threads access at same time - wrong results
       Dead lock      :- multiple threads wait for each other - application freeze
    */

}
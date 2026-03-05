#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<int> buffer;
const unsigned int MAX_SIZE = 5;

mutex m;
condition_variable cv;

void producer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(m);
        // unique_lock locks the mutex.
        
        /* producer wait must buffer is untail full */
        cv.wait(lock, [] { return buffer.size() < MAX_SIZE; });// wait condition 
        // Wait until buffer is NOT full.

        buffer.push(i);// add item
        cout << "Produced: " << i << endl;

        lock.unlock();
        cv.notify_one();

        // Unlock first (better performance).
        // Notify one waiting thread (consumer).
    }
}


void consumer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(m);
        // wait until buffer has data
        cv.wait(lock, [] { return !buffer.empty(); });

        int val = buffer.front();
        buffer.pop(); // remove item
        cout << "Consumed: " << val << endl;

        lock.unlock();// unlock & modify
        cv.notify_one();// Notifies producer that space is available.
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();
}
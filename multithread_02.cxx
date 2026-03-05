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
    /* producer wait must buffer is full */
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [] { return buffer.size() < MAX_SIZE; });

        buffer.push(i);
        cout << "Produced: " << i << endl;

        lock.unlock();
        cv.notify_one();
    }
}


void consumer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [] { return !buffer.empty(); });

        int val = buffer.front();
        buffer.pop();
        cout << "Consumed: " << val << endl;

        lock.unlock();
        cv.notify_one();
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);


    t1.join();
    t2.join();
}
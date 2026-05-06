#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool
{
private:
    vector<thread> workers;
    queue<function<void()>> tasks;

    mutex mtx;
    condition_variable cv;
    bool stop;

public:
    ThreadPool(int num_threads) : stop(false)
    {
        for (int i = 0; i < num_threads; i++)
        {
            workers.push_back(thread([this]()
                                     {
                while (true) {
                    function<void()> task;
                    unique_lock<mutex> lock(this->mtx);

                    // wait for task
                    this->cv.wait(lock, [this]() {
                        return !this->tasks.empty() || this->stop;
                    });

                    // stop condition
                    if (this->stop && this->tasks.empty())
                        return;

                    // get task
                    task = this->tasks.front();
                    this->tasks.pop();

                    lock.unlock();
                    // execute task
                    task();
                } }));
        }
    }

    // Add task to queue
    void enqueue(function<void()> task)
    {
        {
            unique_lock<mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }

    // Destructor
    ~ThreadPool()
    {
        {
            unique_lock<mutex> lock(mtx);
            stop = true;
        }

        cv.notify_all();
        // for (size_t i = 0; i < workers.size(); i++)
        // {
        //     workers[i].join();
        // }
        for (int i = 0; i < workers.size(); i++)
        {
            workers[i].join();
        }
    }
};

int main()
{
    ThreadPool pool(3);
    for (int i = 0; i < 5; i++)
    {
        pool.enqueue([i]()
                     { cout << "Task " << i << " executed by thread "
                            << this_thread::get_id() << endl; });
    }
    return 0;
}

/*  ** Thread Pool **
- 3 worker threads
- A queue of tasks
- threads keep picking tasks and executing them

Thinks like this->
- workes(threads)-chefs
- Queue(tasks)-food orders
- conditon variable-bell to notify chefs

if no orders - chefs sleep
if orders comes - chefs wakes up and cooks

1. Data members
workers - threads doing work
tasks - queue of jobs
mtx - protects queue
cv - tells threads new task available
stop - tells threads to exit




*/
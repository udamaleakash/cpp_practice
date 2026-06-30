// ============================================================
// C++ Multithreading Revision
// Interview Revision Notes
// ============================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
using namespace std;

/*
Topics:
1. Thread Creation
2. join() vs detach()
3. Race Condition
4. mutex
5. lock_guard
6. unique_lock
7. atomic
8. Deadlock
9. condition_variable
10. Producer Consumer
11. Interview Questions
*/

//---------------- Thread Example ----------------
void hello()
{
    cout << "Hello from thread\n";
}

//---------------- Race Condition ----------------
int counter = 0;
mutex mtx;

void increment_mutex()
{
    lock_guard<mutex> lock(mtx);
    counter++;
}

//---------------- Atomic ----------------
atomic<int> atomicCounter(0);

void increment_atomic()
{
    atomicCounter++;
}

int main()
{
    cout << "===== Thread =====\n";
    thread t1(hello);
    t1.join();

    cout << "\n===== Mutex =====\n";
    thread t2(increment_mutex);
    thread t3(increment_mutex);
    t2.join();
    t3.join();
    cout << "Counter = " << counter << endl;

    cout << "\n===== Atomic =====\n";
    thread t4(increment_atomic);
    thread t5(increment_atomic);
    t4.join();
    t5.join();
    cout << "Atomic Counter = " << atomicCounter << endl;

    return 0;
}

/*
Interview Quick Notes

Multithreading
-
Multithreading is the ability of a process to execute multiple threads concurrently.
Threads share the same process memory but execute independently.
It improves CPU utilization, responsiveness, and performance.

Race Condition
- Multiple threads access shared data simultaneously.

Mutex
- Prevents race condition.
- lock() / unlock()

lock_guard
- Automatically unlocks (RAII).

unique_lock
- Flexible.
- Can unlock manually.
- Works with condition_variable.

Atomic
- Lock-free for simple operations.
- Faster than mutex for counters.

Deadlock
- Two threads waiting forever for each other.

Condition Variable
- wait()
- notify_one()
- notify_all()

Producer Consumer
- queue + mutex + condition_variable


C++ MULTITHREADING INTERVIEW QUESTIONS & ANSWERS
===============================================

1. What is Multithreading?
Answer:
Multithreading is the ability of a process to execute multiple threads concurrently.
Threads share the same process memory but execute independently.
It improves CPU utilization, responsiveness, and performance.

Example:
Browser:
- UI Thread
- Network Thread
- Rendering Thread

------------------------------------------------------------

2. Difference between Process and Thread?

Process
- Independent execution unit
- Separate memory space
- Heavyweight
- Slow context switching
- IPC required

Thread
- Smallest execution unit
- Shared memory
- Lightweight
- Faster context switching
- Easy communication

------------------------------------------------------------

3. What is Race Condition?

Answer:
A race condition occurs when multiple threads access and modify shared data simultaneously
without proper synchronization, causing unpredictable results.

Solution:
- mutex
- atomic
- synchronization primitives

------------------------------------------------------------

4. Mutex vs Semaphore

Mutex
- Ownership based
- Only owner unlocks
- Binary lock
- Used for protecting shared resources

Semaphore
- Counter based
- Any thread may signal
- Controls access to limited resources
- Supports binary and counting semaphore

------------------------------------------------------------

5. Atomic vs Mutex

Atomic
- Lock-free for simple operations
- Faster
- Used for counters/flags
- No blocking

Mutex
- Supports complex critical sections
- Slightly slower
- Thread blocking possible
- Protects multiple variables

------------------------------------------------------------

6. Why is lock_guard RAII?

RAII = Resource Acquisition Is Initialization.

lock_guard acquires the mutex in its constructor and automatically releases it
in its destructor, preventing forgotten unlocks and exception-related deadlocks.

------------------------------------------------------------

7. Why unique_lock with condition_variable?

condition_variable::wait() temporarily unlocks the mutex while waiting and
locks it again when notified.

Only unique_lock provides this flexibility.

------------------------------------------------------------

8. join() vs detach()

join()
- Parent waits
- Safe
- Synchronizes thread completion

detach()
- Thread runs independently
- Parent doesn't wait
- Cannot join later
- Risk if detached thread accesses destroyed objects

------------------------------------------------------------

9. What happens if thread object is destroyed?

If a std::thread object is destroyed while still joinable(),
the program calls std::terminate().

Always call:
- join()
OR
- detach()

------------------------------------------------------------

10. What is False Sharing?

False sharing occurs when multiple threads modify different variables located
on the same CPU cache line, causing unnecessary cache invalidations and reducing performance.

Solution:
- Align variables
- Add padding
- Use alignas()

------------------------------------------------------------

11. What is Cache Line?

Cache line is the smallest block of memory transferred between main memory
and CPU cache (typically 64 bytes).

Threads sharing one cache line may suffer false sharing.

------------------------------------------------------------

12. What is ABA Problem?

ABA occurs in lock-free programming.

A value changes:
A -> B -> A

Another thread only sees A again and assumes nothing changed,
which may lead to incorrect behavior.

Solution:
- Version counters
- Tagged pointers
- Hazard pointers

------------------------------------------------------------

13. Why is Atomic Faster?

Atomic operations are usually implemented using CPU hardware instructions.

They avoid:
- OS scheduling
- Lock acquisition
- Context switching
However, atomics are suitable only for simple operations.



Interview Tip:
For every answer, explain:
1. Definition
2. Why it is needed
3. Real-world example
4. Advantages
5. Limitations


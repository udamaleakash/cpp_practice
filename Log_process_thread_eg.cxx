/* Multithreading Example */

/* Log Processing with Threads */
/* log1.txt ,2 ,3 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
using namespace std;

mutex mtx; // protects shared data
int total_errors = 0;

// Function executed by each thread
void process_log(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        /* Either user lock_guard or mtx.lock & mtx.unlock */
        // lock_guard<mutex> lock(mtx);
        mtx.lock();
        cout << "Failed to open: " << filename << endl;
        return;
        mtx.unlock();
    }
    string line;
    int local_errors = 0;

    // Read file line by line
    while (getline(file, line))
    {
        if (line.find("ERROR") != string::npos)
        /* here npos is used to signify substring not found*/
        {
            mtx.lock();
            local_errors++;
            mtx.unlock();
        }
    }
    // Update shared result safely
    // lock_guard<mutex> lock(mtx);
    mtx.lock();
    total_errors += local_errors;
    cout << filename << " -> Errors: " << local_errors << endl;
    mtx.unlock();
}

int main()
{
    vector<string> files = {
        "log1.txt",
        "log2.txt",
        "log3.txt"
    };

    vector<thread> threads;
    // Create threads
    for (const auto &file : files)
    {
        // threads.emplace_back(process_log, file);
        threads.push_back(thread(process_log,file));
    }

    // Join threads
    for (auto &t : threads)
    {
        t.join();
    }
    cout << "Total Errors: " << total_errors << endl;
    return 0;
}
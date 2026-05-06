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
        lock_guard<mutex> lock(mtx);
        cout << "Failed to open: " << filename << endl;
        return;
    }
    string line;
    int local_errors = 0;

    // Read file line by line
    while (getline(file, line))
    {
        if (line.find("ERROR") != string::npos)
        {
            local_errors++;
        }
    }

    // Update shared result safely
    {
        lock_guard<mutex> lock(mtx);
        total_errors += local_errors;
        cout << filename << " -> Errors: " << local_errors << endl;
    }
}

int main()
{
    vector<string> files = {
        "log1.txt",
        "log2.txt",
        "log3.txt"};

    vector<thread> threads;
    // Create threads
    for (const auto &file : files)
    {
        threads.emplace_back(process_log, file);
    }

    // Join threads
    for (auto &t : threads)
    {
        t.join();
    }

    cout << "Total Errors: " << total_errors << endl;

    return 0;
}
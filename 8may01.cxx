#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mtx;
class Account
{
public:
    void saving_deposit(int a, int b)
    {
        lock_guard<mutex> lock(mtx); // auto lock / unlock
        cout << "Saving deposit: " << a << " + " << b << " = " << a + b << endl;
    }
};

int main()
{
    Account acc;
    thread t1(&Account::saving_deposit, &acc, 100000, 200000);
    thread t2(&Account::saving_deposit, &acc, 300000, 400000);

    t1.join();
    t2.join();

    vector<thread> threads;
    for (int i = 0; i < 5; i++)
    {
        threads.push_back(thread(&Account::saving_deposit, &acc, 500000, 300000));
    }
    
    vector<thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++)
    {
        it->join();
    }

    return 0;
}
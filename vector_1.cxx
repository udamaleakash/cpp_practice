#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // 1. create a vector
    vector<int> v;
    // 2. add in vector
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // 3. print vector
    // index
    for (int i = 0; i < v.size(); i++)
    {
        // cout << v[i] << endl;
    }
    // Range based for
    for (int a : v)
    {
        // cout << a << " ";
    }
    // Iterator
    for (auto it = v.begin(); it != v.end(); it++)
    {
        // cout << *it << " ";
    }
    // cout << v.size() << endl; // 3
    // cout << v.capacity();     // 4
    /*
size()	Number of elements
capacity()	Allocated storage */

    v.insert(v.begin(), 11);
    v.insert(v.end(), 99);
    v.erase(v.begin() + 2);
    // sort(v.begin(), v.end());
    for (int a : v)
    {
        cout << a << " ";
    } // 11 10 30 99

    return 0;
}
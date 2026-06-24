#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

void find_2nd_max(int arr[], int len)
{
    int first = INT_MIN;
    int sec = INT_MIN;
    int third = INT_MIN;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] > first) // largest
        {
            third = sec;
            sec = first;
            first = arr[i];
        }
        else if (arr[i] > sec && arr[i] != sec) // 2nd largest
        {
            third = sec;
            sec = arr[i];
        }
        else if (arr[i] > third && arr[i] != first && arr[i] != sec) // 3rd largest
        {
            third = arr[i];
        }
    }
    if (first != INT_MIN)
        cout << "largest element:" << first << endl;
    if (sec != INT_MIN)
        cout << "2nd largest element:" << sec << endl;
    if (third != INT_MIN)
        cout << "Third largest element:" << third << endl;
}
int main()
{
    int arr[] = {23, 56, 34, 56, 34, 12, 890, 456, 345, 876, 23, 45, 90, 90, 23, 56, 56, 56, 34, 34};
    int len = sizeof(arr) / sizeof(arr[0]);
    find_2nd_max(arr, len);

    sort(arr, arr + len);
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\nAfter Remove Duplicates" << endl;
    vector<int> v1 = {23, 56, 34, 56, 34, 12, 890, 456, 345, 876, 23, 45, 90, 90, 23, 56, 56, 56, 34, 34};

    sort(v1.begin(), v1.end());
    vector<int>::iterator it1;
    v1.erase(unique(v1.begin(), v1.end()), v1.end());
    for (it1 = v1.begin(); it1 != v1.end(); it1++)
    {
        cout << *it1 << " ";
    }
    cout << endl;

    // using set
    /* fisrt store in vector then insert in set */
    cout << "Using Set" << endl;
    set<int> s1;
    vector<int> v2 = {23, 56, 34, 56, 34, 12, 890, 456, 345, 876, 23, 45, 90, 90, 23, 56, 56, 56, 34, 34};
    vector<int>::iterator it2;

    for (it2 = v2.begin(); it2 != v2.end(); it2++)
    {
        s1.insert(*it2);
    }

    set<int>::iterator it3;
    for (it3 = s1.begin(); it3 != s1.end(); it3++)
    {
        cout << *it3 << " ";
    }
}
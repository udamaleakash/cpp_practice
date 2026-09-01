#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int, int> mp;
    int arr[] = {23, 56, 34, 56, 34, 12, 90, 90, 23};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    for (i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }

    map<int, int>::iterator it;
    for (it = mp.begin(); it != mp.end(); ++it)
    {
        cout << it->first << " :"<<it->second<<endl;
    }
    cout << endl;
    return 0;
};

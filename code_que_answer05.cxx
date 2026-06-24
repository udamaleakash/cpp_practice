#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

void revise_arr()
{
    cout << "\n===== ARRAY =====\n";

    int arr[] = {23, 56, 34, 56, 34, 12, 90, 90, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort
    sort(arr, arr + n); // O(n log n)

    cout << "Sorted Array : ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    // Remove duplicates manually
    cout << "Unique Elements : ";

    cout << arr[0] << " ";

    for (int i = 1; i < n; i++)
    {
        if (arr[i] != arr[i - 1])
        {
            cout << arr[i] << " ";
        }
    }

    cout << endl;
}

void revise_vector()
{
    cout << "\n===== VECTOR =====\n";

    vector<int> v;

    v.push_back(23);
    v.push_back(56);
    v.push_back(34);
    v.push_back(56);
    v.push_back(34);
    v.push_back(12);
    v.push_back(90);
    v.push_back(90);

    // Sort
    sort(v.begin(), v.end()); // O(n log n)

    cout << "Sorted Vector : ";

    vector<int>::iterator it;

    for (it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;

    // Remove Duplicates
    v.erase(unique(v.begin(), v.end()), v.end());
    cout << "After Remove Duplicates : ";

    for (it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
}

void revise_set()
{
    cout << "\n===== SET =====\n";

    set<int> s;

    s.insert(23);
    s.insert(56);
    s.insert(34);
    s.insert(56);
    s.insert(34);
    s.insert(12);
    s.insert(90);
    s.insert(90);

    // Automatically Sorted + Unique
    // Insert : O(log n)

    cout << "Set Elements : ";

    set<int>::iterator it;

    for (it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
}

void revise_map()
{
    cout << "\n===== MAP =====\n";

    map<int, int> mp;

    int arr[] = {23, 56, 34, 56, 34, 12, 90, 90, 23};

    int n = sizeof(arr) / sizeof(arr[0]);

    int i;

    for (i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }

    cout << "Unique Keys : ";

    map<int, int>::iterator it;

    for (it = mp.begin(); it != mp.end(); ++it)
    {
        cout << it->first << " ";
    }

    cout << endl;

    cout << "Frequency :\n";

    for (it = mp.begin(); it != mp.end(); ++it)
    {
        cout << it->first << " -> "
             << it->second << endl;
    }
}

int main()
{
    revise_arr();
    revise_vector();
    revise_set();
    revise_map();

    return 0;
}
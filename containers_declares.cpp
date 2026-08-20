#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>

using namespace std;

int main()
{
    string name = "I $have a$ book$"; // remove $
    string result;
    for (char &ch : name)
    {
        if (ch != '$')
            result += ch;
        // ch = 'S';
    }
    // cout << name << endl;

    char name2[] = "I $Have A$ Book$"; // remove $
    int k = 0;
    for (int i = 0; name2[i] != '\0'; i++)
    {
        if (name2[i] != '$')
        {
            name2[k++] = name2[i];
        }
    }
    name2[k] = '\0';
    cout << name2 << "\n";

    int arr[] = {1, 2, 3, 4, 5};
    char str[] = "Hello";
    set<int> s = {23, 56, 56, 78, 23, 4, 90};
    vector<int> v = {23, 56, 56, 78, 23, 4, 90};
    map<int, int> m = {{56, 78}, {23, 56}, {23, 4}, {90, 0}};
    unordered_map<int, int> m2 = {{56, 78}, {23, 56}, {23, 4}, {90, 0}};
    multimap<int, int> m3 = {{56, 78}, {23, 56}, {23, 4}, {90, 0}};
    unordered_multimap<int, int> m4 = {{56, 78}, {23, 56}, {23, 4}, {90, 0}};
    list<int> l = {23, 56, 56, 78, 23, 4, 90};
    list<int> l2 = {23, 56, 56, 78, 23, 4, 90};

    for (auto t : m3)
    {
        cout << t.first << "," << t.second << endl;
        // cout << t << endl;
    }
    for (auto &[key, value] : m) // structural binding printing
    {
        // cout << key << " " << value << endl;
    }
    map<int, int>::iterator it1;
    auto it2 = m.find(23); // find in map

    if (it2 != m.end())
    {
        // cout << it2->first << " " << it2->second << endl;
    }

    for (it2 = m.begin(); it2 != m.end(); it2++)
    {
        // cout << it2->first << " " << it2->second << endl;
        // i want find 23 in map and print its value
        // using map find function
    }
    // Now for next part refer file vector_1.cxx

    return 0;
}
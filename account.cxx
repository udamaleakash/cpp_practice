#include <iostream>
#include <climits>
using namespace std;

void second_max_element_arr()
{
    int arr[] = {11, 56, 56, 78, 78, 11, 11, 78, 34, 34, 223, 223};

    int len = sizeof(arr) / sizeof(arr[0]);
    int first = INT_MIN;
    int second = INT_MIN;
    int third = INT_MIN; // we use here 0 also when non-negative number assign
                         /* so the logic works for:(INT_MIN)
                         - positive numbers
                         - negative numbers
                         - mixed numbers
                         */

    for (int i = 0; i < len; i++)
    {
        if (arr[i] > first) // update largest
        {
            third = second;
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first) // update second largest
        {
            third = second;
            second = arr[i];
        }
        else if (arr[i] > third && (arr[i] != first && arr[i] != third))
        {
            third = arr[i];
        }
    }

    if (second == INT_MIN || third == INT_MIN)
    {
        if (second == INT_MIN)
            cout << "Second largest element not found";
        else
            cout << "Third largest element not found";
    }
    else
    {
        cout << "Largest = " << first << endl;
        cout << "Second Largest = " << second << endl;
        cout << "Third Largest = " << third << endl;
    }
}

#include <vector>
#include <algorithm>
void use_2nd_way()
{
    vector<int> v = {11, 56, 56, 78, 34, 223};
    sort(v.begin(), v.end());
    vector<int>::iterator it1;
    for (it1 = v.begin(); it1 != v.end(); it1++)
    {
        cout << *it1 << " ";
    }
    cout << "\n"
         << *(v.end() - 2) << endl;
}
void use_vector()
{
    vector<int> v = {11, 56, 56, 78, 34, 223};

    nth_element(v.begin(), v.end() - 2, v.end()); // not sorted here
    /*  syntax-> nth_element(first, nth, last) */

    cout << "Second largest: " << *(v.end() - 2) << '\n';
    /* Notice:

78 is at index 4 (v.end()-2) ✔
All elements before 78 are <= 78 ✔
All elements after 78 are >= 78 ✔
But the first part is not sorted (34 11 56 56) ❌ */

    use_2nd_way();
}
int main()
{
    // second_max_element_arr();
    use_vector();
    return 0;
}
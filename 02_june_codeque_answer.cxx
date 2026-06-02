#include <iostream>
#include <climits>
using namespace std;

void find_second_max_element_arr()
{
    int arr[] = {-11, 56, 56, 78, 78, -11, -11, 78, 34, 34, 223, 223};

    int len = sizeof(arr) / sizeof(arr[0]);
    int first = INT_MIN;
    int second = INT_MIN; // we use here 0 also when non-negative number assign
    /* so the logic works for:(INT_MIN)
    - positive numbers
    - negative numbers
    - mixed numbers
    */

    for (int i = 0; i < len; i++)
    {
        // Update largest
        if (arr[i] > first)
        {
            second = first;
            first = arr[i];
        }
        // Update second largest
        else if (arr[i] > second && arr[i] != first)
        {
            second = arr[i];
        }
    }

    if (second == INT_MIN)
    {
        cout << "Second largest element not found";
    }
    else
    {
        cout << "Largest = " << first << endl;
        cout << "Second Largest = " << second << endl;
    }
}

void find_third_max_element_arr()
{
    int arr[] = {11, 56, 56, 78, 78, 11, 11, 78, 34, 34, 223, 223};
    int len = sizeof(arr) / sizeof(arr[0]);
    int first = INT_MIN;
    int second = INT_MIN;
    int third = INT_MIN;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] > first)
        {
            third = second;
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first)
        {
            third = second;
            second = arr[i];
        }
        else if (arr[i] > third && (arr[i] != first && arr[i] != second))
        {
            third = arr[i];
        }
    }

    if (first != INT_MIN)
        cout << " Largest Element: " << first;
    if (second != INT_MIN)
        cout << " Second Largest Element: " << second;
    if (third != INT_MIN)
        cout << " Third Largest Element: " << third << endl;
}

void find_four_max_element_arr()
{
    int arr[] = {11, 56, 56, 78, 78, 11, 11, 78, 34, 34, 223, 223};
    int len = sizeof(arr) / sizeof(arr[0]);
    int first = INT_MIN;
    int second = INT_MIN;
    int third = INT_MIN;
    int fourth = INT_MIN;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] > first) // largest
        {
            fourth = third;
            third = second;
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first) // 2nd largest
        {
            fourth = third;
            third = second;
            second = arr[i];
        }
        else if (arr[i] > third && (arr[i] != first && arr[i] != second && arr[i] != fourth)) // 3rd largest
        {
            fourth = third;
            third = arr[i];
        }
        else if (arr[i] > fourth && (arr[i] != first && arr[i] != second && arr[i] != third)) // 4th largest
        {
            fourth = arr[i];
        }
    }

    if (first != INT_MIN)
        cout << " Largest Element: " << first;
    if (second != INT_MIN)
        cout << " Second Largest Element: " << second;
    if (third != INT_MIN)
        cout << " Third Largest Element: " << third;
    if (fourth != INT_MIN)
        cout << " Fourth Largest Element: " << fourth << endl;
}

int main()
{
    /* Find the 1st, 2nd, 3rd & 4th Maximum element from array. (here use climits INT_MIN) */
    cout << "1) " << endl;
    find_second_max_element_arr();
    cout << "2) " << endl;
    find_third_max_element_arr();
    cout << "3) " << endl;
    find_four_max_element_arr();

    return 0;
}
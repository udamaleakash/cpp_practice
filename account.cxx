#include <iostream>
#include <climits>
using namespace std;

void second_max_element_arr()
{
    int arr[] = {11, 11, 11, 56, 56, 78, 78, 78, 34, 34, 223, 223};

    int len = sizeof(arr) / sizeof(arr[0]);

    int first = INT_MIN;
    int second = INT_MIN;

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

int main()
{
    second_max_element_arr();
    return 0;
}
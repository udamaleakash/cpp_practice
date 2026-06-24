#include <iostream>
#include <cstring>
using namespace std;

// Here String & Array
// Reverse using Recursion
// Start & End approach - swap it

void reverse_str_recursion(char str[], int start, int end) // char string
{
    if (start >= end)
        return;

    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverse_str_recursion(str, start + 1, end - 1);
}

void reverse_arr_recursion(int arr[], int start, int end) // array
{
    if (start >= end) // start, end apparoch
        return;

    int temp = arr[start]; // swap it
    arr[start] = arr[end];
    arr[end] = temp;

    reverse_arr_recursion(arr, start + 1, end - 1); // call function with postion decrement
}

int main()
{
    // string reverse using recursion
    char str1[] = "Customer ID";
    reverse_str_recursion(str1, 0, strlen(str1) - 1);
    cout << str1;

    cout << endl;
    // array reverse using recursion
    int arr[] = {34, 67, 12, 0, 88, 96, 47};
    int len = sizeof(arr) / sizeof(arr[0]);
    reverse_arr_recursion(arr, 0, len - 1); // here 0= start & len-1 =end
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}

#include <stdio.h>
#include <iostream>
using namespace std;

class Base
{
public:
    virtual void show()
    {
        cout << "Base";
    }
};
class Derived : public Base
{
public:
    void show()
    {
        cout << "Derived";
    }
};

#include <string>
void accountno_reverse_string_1(string str) // using string
{
    // two pointer approach use here
    int l = 0;
    int r = str.length() - 1;

    while (l < r)
    {
        swap(str[l], str[r]);
        l++;
        r--;
    }
    cout << str << endl;
}

#include <string.h>
void accountno_reverse_string_2(char *str) // using char *str
{
    // two pointer approach use here
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    cout << str << endl;
}

bool customerid_is_palindrome(char *str)
{
    // two end point char apparoch here
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j)
    {
        if (str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

void remove_duplicate_element_arr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (arr[i] == arr[j])
            {
                for (int k = j; k < len; k++)
                {
                    arr[k] = arr[k + 1]; /* to remove = duplicate element replaced by next element */
                }
                len--; /* when duplicate element remove then size decrease by one */
            }
        }
        cout << arr[i] << " ";
    }
}
void second_max_element_arr()
{
    int arr[] = {11, 11, 11, 56, 56, 78, 78, 78, 34, 34, 223, 223};
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len;)
        {
            if (arr[i] == arr[j])
            {
                for (int k = j; k < len; k++)
                {
                    arr[k] = arr[k + 1];
                }

                len--;
            }
            else
            {
                j++;
            }
        }
    }

    // Print unique sorted array
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n2nd max is: " << arr[1] << endl;
}

void fibbnacii_series(int n)
{
    int a = 0, b = 1;
    cout << "\nFiboo: " << a << " " << b << " ";
    for (int i = 2; i < n; i++)
    {
        // a + b = c
        int c = a + b;
        cout << c << " ";
        /* 0 1 1 2 3 5 8 13 21 .
           a b c|a b c|a  b c  .
         */
        a = b;
        b = c;
    }
}

void merge_two_sorted_arr(int arr1[], int arr2[], int len1, int len2)
{
    int arr3[len1 + len2];
    for (int i = 0; i < len1 + len2; i++)
    {
        if (i < len1)
            arr3[i] = arr1[i];
        else
            arr3[i] = arr2[i - len1]; // to access arr2 from 0 index after len1 elements = arr2[5-5]= arr2[0] like this
        cout << arr3[i] << " ";
    }
}

int main()
{
    /* 1) */
    Base *ptr = new Derived();
    ptr->show();

    /* 2) */
    int x = 10;
    int *const p = &x;
    cout << *p;

    /* 3) */
    char *ptrx = new char[100]; // ptrx is a variable-> stack & actual int 100-> heap
    delete[] ptrx;

    // 4)
    accountno_reverse_string_1("0001129000788");

    // 5)
    char str[] = "0001129000788";
    accountno_reverse_string_2(str);

    // 6)
    char str2[] = "105501";
    if (customerid_is_palindrome(str2)) // take bool fun for palindrome logic
        cout << "plaindrome\n";
    else
        cout << "Not plaindrome\n";

    // 7)
    cout<<"7:->\n";
    int arr[] = {12, 45, 12, 45, 67, 7, 89, 900, 89};
    int len = sizeof(arr) / sizeof(arr[0]);
    remove_duplicate_element_arr(arr, len);
    cout << endl;
    second_max_element_arr(); // 2nd max element in arr // using loop, high complexity

    // 8)
    fibbnacii_series(10); // c = a + b & a = b = c
    cout << endl;

    // 9)
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    merge_two_sorted_arr(arr1, arr2, len1, len2);
    cout << endl;

    return 0;
}
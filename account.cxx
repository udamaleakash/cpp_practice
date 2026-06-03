#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sort_arr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    cout << "\nAfter Sort Array: " << endl;
}
void remove_duplicates(int arr[], int &len)
{
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
    cout << "\nAfter Remove Duplicates: " << endl;
}
void display_arr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << ",";
    }
}
void using_regular_way(int arr[], int &len)
{
    sort_arr(arr, len);
    display_arr(arr, len);
    remove_duplicates(arr, len);
    display_arr(arr, len);
}
void using_vector(vector<int> v)
{
    cout << "Using After vector: \n"
         << endl;
    vector<int>::iterator it;
    sort(v.begin(), v.end());

    v.erase(unique(v.begin(), v.end()), v.end());
    for (it = v.begin(); it != v.end(); it++)
    {
        cout << *it << ",";
    }
    cout << "\n2nd largest field: " << *(v.end() - 2) << endl;
}
void move_zeros_to_end(int arr[], int &len)
{
    int count = 0;
    for (int i = 0; i < len; i++) /* 1st all non-zeros values fill */
    {
        if (arr[i] != 0)
        {
            arr[count++] = arr[i];
        }
    }
    while (count < len) /* then add remain with zeros */
    {
        arr[count++] = 0;
    }
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
}
void move_zeros_to_start(int arr[], int &len)
{
    cout << "\nMove_zeros_to_start\n"
         << endl;
    int count = len-1;
    for (int i = len-1; i >= 0; i--)
    {
        if (arr[i] != 0)
        {
            arr[count--] = arr[i];
        }
    }

    while (count >= 0)
    {
        arr[count--] = 0;
    }
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
}

int main()
{
    /* Sort and remove duplicates */
    int arr[] = {0, 11, 11, 44, 0, 77, 33, 66, 99, 22, 11, 55, 77, 22, 33, 897, 435, 678, 22, 66, 22, 33, 44, 66, 66, 33, 44, 0};
    int len = sizeof(arr) / sizeof(arr[0]);
    using_regular_way(arr, len);

    vector<int> v1 = {0, 11, 11, 44, 0, 77, 33, 66, 99, 22, 11, 55, 77, 22, 33, 897, 435, 678, 22, 66, 22, 33, 44, 66, 66, 33, 44, 0};
    cout << "\n";
    using_vector(v1);
    cout << "\n";

    /* Move Zeros in arary */
    cout << "\n Move zeros to End position" << endl;
    int arr2[] = {0, 1, 0, 3, 12, 56, 0, 67, 0, 45};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    move_zeros_to_end(arr2, len2);
    move_zeros_to_start(arr2, len2);

    
    return 0;
}
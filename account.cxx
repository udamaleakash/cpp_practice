#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int binary(int arr[], int len, int key)
{
    int low = 0;
    int high = len - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
int main()
{
    int arr[] = {11, 33, 32, 67, 21, 3, 89};
    int len = sizeof(arr) / sizeof(arr[0]);
    sort(arr, arr + len);
    for (auto it : arr)
    {
        cout << it << " ";
    }
    cout<<endl;
    int result = binary(arr, len, 67);
    if (result != -1)
        cout << arr[result] << " is found at " << result << " index ";

    return 0;
}
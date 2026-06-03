#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

void find_second_max_element_arr(int arr[], int len)
{

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

void find_third_max_element_arr(int arr[], int len)
{
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

void find_four_max_element_arr(int arr[], int len)
{
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
void use_vector(vector<int> v)
{
    cout << "2nd way-> ";
    sort(v.begin(), v.end());
    vector<int>::iterator it1;
    v.erase(unique(v.begin(), v.end()), v.end());
    for (it1 = v.begin(); it1 != v.end(); it1++)
    {
        cout << *it1 << " ";
    }

    cout << "\nSecond largest: "
         << *(v.end() - 2) << endl; // similarly we can find 3rd largest: *(v.end() - 3) and 4th largest: *(v.end() - 4)
}

//

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
    int count = len - 1;
    for (int i = len - 1; i >= 0; i--)
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
    /* Coding Que & answers */
    /* Find the 1st, 2nd, 3rd & 4th Maximum element from array. (here use climits INT_MIN) */
    int arr[] = {11, 56, 56, 78, 78, 11, 11, 78, 34, 34, 223, 223};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "1) " << endl;
    find_second_max_element_arr(arr, len);
    cout << "2) " << endl;
    find_third_max_element_arr(arr, len);
    cout << "3) " << endl;
    find_four_max_element_arr(arr, len); // write once function to get all first to fourth element
    /* For above time complexity: O(n) and space complexity: O(1) */

    /* Now using vector */
    vector<int> v = {11, 56, 56, 78, 78, 11, 11, 78, 34, 34, 223, 223};
    use_vector(v); // Time complexity: O(n log n) and space complexity: O(n) because of sorting and storing unique elements in vector.

    /* Which is Faster first one or second one?
       First one is faster than the second one because of time complexity. But the second one is more readable and less error-prone than the first one. */

    //

    /* Sort and remove duplicates */
    int arr1[] = {0, 11, 11, 44, 0, 77, 33, 66, 99, 22, 11, 55, 77, 22, 33, 897, 435, 678, 22, 66, 22, 33, 44, 66, 66, 33, 44, 0};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    using_regular_way(arr1, len1);

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
#include <iostream>
using namespace std;

void odd_even_print(int arr[], int len)
{
    cout << "odd even print\n";
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] % 2 != 0)
        {
            int temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
            index++;
        }
    }
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
}

void move_zeros_to_end()
{
    cout << "\nmove_zeros_to_end\n";
    int arr[] = {0, 1, 0, 3, 12};
    int len = sizeof(arr) / sizeof(arr[0]);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] != 0)
        {
            int temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
            index++;
        }
    }
    for (int i : arr)
    {
        cout << i << " ";
    }
}

void move_negative_to_left()
{
    cout << "\nmove_negative_to_left\n";
    int arr[] = {1, -2, 3, -4, 5, -6};
    int len = sizeof(arr) / sizeof(arr[0]);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] < 0)
        {
            int temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
            index++;
        }
    }
    for (int i : arr)
    {
        cout << i << " ";
    }
}

void separate_even_odd()
{
    cout << "\nseparate_even_odd\n";
    int arr[] = {2, 7, 4, 9, 6, 3, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] % 2 != 0) // odd
        {
            int temp = arr[i];
            // Shift elements right
            for (int j = i; j > index; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[index] = temp;
            index++;
        }
    }
    for (int i : arr)
    {
        cout << i << " ";
    }
}

void remove_duplicate_arr()
{
    cout << "\nRemove_duplicate_arr\n";
    int arr[] = {1, 1, 2, 2, 3, 4, 4};
    int len = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len;)
        {
            if (arr[i] == arr[j])
            {
                for (int k = j; k < len - 1; k++)
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
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
}
#include <climits>
void find_second_largest()
{
    cout << "\nFind second largest\n";
    int arr[] = {10, 5, 20, 8, 20, 15, 16};
    int len = sizeof(arr) / sizeof(arr[0]);

    int first = INT_MIN;
    int second = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] > first)
        {
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first)
        {
            second = arr[i];
        }
    }
    if (second != INT_MIN)
        cout << "second largest:" << second << endl;
}
void find_missing_numbers()
{
    cout << "\nFind_missing_numbers\n";
    // int arr[] = {1, 2, 9, 4, 7}; // 3,5,6,8

    int arr[] = {9, 4, 7, 11}; // 5,6,8,10

    int len = sizeof(arr) / sizeof(arr[0]);

    int max = 0;
    for (int i = 0; i < len; i++) // find max
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    // check no.s from 1 to max
    for (int i = 1; i <= max; i++) // outer loop 1 to max
    {
        bool found = false;
        for (int j = 0; j < len; j++) // inner loop for input array
        {
            if (i == arr[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
            cout << i << " ";
    }
}
// 3, 5, 6 ,8

void count_vowels_consonts()
{
    cout << "\ncount_vowels_consonts\n";
    string str = " i am Akash 1234";
    int v = 0, c = 0;
    char vowels[20], conso[20];
    for (int i = 0; i < str.length(); i++)
    {
        if (isalpha(str[i]))
        {
            char ch = tolower(str[i]);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            {
                vowels[v++] = ch;
            }
            else
            {
                conso[c++] = ch;
            }
        }
    }
    vowels[v] = '\0';
    conso[c] = '\0';
    cout << "\n Vowels : " << vowels << "\n Consonts: " << conso << endl;
}

int main()
{
    int arr[] = {2, 4, 5, 10, 33, 6, 89};
    int len = sizeof(arr) / sizeof(arr[0]);
    odd_even_print(arr, len);

    move_zeros_to_end();

    move_negative_to_left();

    separate_even_odd();

    remove_duplicate_arr();

    find_second_largest();

    find_missing_numbers();

    count_vowels_consonts();

    return 0;
}
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int two_sum()
{
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int len = sizeof(nums) / sizeof(nums[0]);

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (nums[i] + nums[j] == target)
                cout << "[" << i << "," << j << "]";
        }
    }
    return 0;
}

void productExceptSelf()
{
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    int answer[n];

    int prefix = 1;

    // left products
    for (int i = 0; i < n; i++)
    {
        answer[i] = prefix;
        prefix *= nums[i];
    }

    int suffix = 1;

    // right products
    for (int i = n - 1; i >= 0; i--)
    {
        answer[i] *= suffix;
        suffix *= nums[i];
    }

    for (int i = 0; i < n; i++)
        cout << answer[i] << " ";
}
bool is_palindrome(string s)
{
    int left = 0;
    int right = s.size() - 1;
    string result(s.size(), ' ');

    while (left < right)
    {
        // left
        while (left < right && !isalnum(s[left]))
            left++;
        // skip not alpha numeric

        // right
        while (left < right && !isalnum(s[right]))
            right--;

        if (tolower(s[left]) != tolower(s[right]))
        {
            return false;
        }
        else
        {
            result[left] = tolower(s[left]);
            result[right] = tolower(s[right]);
        }

        left++;
        right--;
    }
    cout << result << endl;
    return true;
}
void validate_palindrome()
{
    string s = "A man, a plan, a canal: Panama";
    if (is_palindrome(s))
        cout << " Palindrome ";
    else
        cout << " Not Palindrome ";
}

int main()
{
    // two_sum();
    /* Product of Array Except Self */
    // productExceptSelf();
    validate_palindrome();
    return 0;
}
// Q1. Briefly introduce yourself focusing on:

// your current role

// what you built in CBS

// your strongest C++ skills

// why you want to switch
// Hi, my name is Akash Udamale.
// my current role is software developer at kimaya infotech pvt. ltd.
// i worked on CBS banking domain as c++ developer.
// working on various modules like customer form, reconsacation form RBI reports , cts clearing module
// using c++ oops concepts, STL, multithreading, and dsa.
// i want carrer grouth and use my techncal skills to big level organzzation like yours.
// thank you. 

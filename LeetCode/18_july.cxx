/*
Q1.
nums = [2,7,11,15]
target = 9

Output:
[0,1]
*/
#include <iostream>
using namespace std;
int main()
{
    int nums[] = {1, 2, 11, 15, 7};
    int target = 9;

    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (nums[i] + nums[j] == target)
                cout << i << " " << j << endl;
        }
    }

    return 0;
}
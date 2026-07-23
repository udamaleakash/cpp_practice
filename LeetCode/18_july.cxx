/*
Q1.
nums = [2,7,11,15]
target = 9

Output:
[0,1]
*/
#include <iostream>
using namespace std;

void result(int nums[], int target)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (nums[i] + nums[j] == target)
                cout << i << " " << j << endl;
        }
    }
}
using namespace std;
int main()
{
    int nums[] = {1, 2, 11, 15, 7};
    int target = 9;

    result(nums, target);

    return 0;
}


/*
GDB commands
g++ -g 18_july.cxx -o 18_july
gdb ./18_july
run
break main
next
print nums
print target
next
break result
next
print i
list - current line
info breakpoints
info locals
info args
continue
step
delete 1 2 - delete breakpoints 1 and 2
quit
 */
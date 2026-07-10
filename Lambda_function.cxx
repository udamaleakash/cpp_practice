/*  Lambda Function:
->  Lambda functions were introduced in C++11. They are anonymous functions (functions without a name) that you can define and use  directly where they're needed.
Think of them as small, temporary functions.

Advantages:-
Less code
No need to create a separate function
Easy to use with STL algorithms
Improves readability for short operations
Can capture local variables

Why is Lambda Used?

It is commonly used with STL algorithms like:

sort()
find_if()
for_each()
count_if()
remove_if()
transform()

Suppose you want to sort numbers.

Without lambda:

bool compare(int a,int b)
{
    return a>b;
}

sort(v.begin(), v.end(), compare);

With lambda:

sort(v.begin(), v.end(),
[](int a,int b)
{
    return a>b;
});

No separate function is needed.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> v = {1, 2, 3, 4, 5};

    // 1)
    sort(v.begin(), v.end(),
         [](int a, int b)
         {
             return a > b;
         });

    for (int x : v)
        cout << x << " ";
    cout << "\n\n"
         << endl;

    // 2)
    for_each(v.begin(), v.end(), [](int x)
             { cout << x << " "; });
    return 0;
};
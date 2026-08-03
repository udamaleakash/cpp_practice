#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <memory>

using namespace std;

int main()
{
    int *ptr = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i <= 9; i++)
    {
        ptr[i] = i + 1;
        cout << ptr[i] << " ";
    }

    free(ptr);
    return 0;
}
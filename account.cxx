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
    int *ptr = (int *)malloc(10 * sizeof(int)); // here , using pointer store 10 elements & print dynamic memory allocate
    for (int i = 0; i <= 9; i++)
    {
        ptr[i] = i + 1;
        cout << ptr[i] << " ";
    }
    free(ptr);

    /* A void* is a generic pointer that can store the address of any data type, but it cannot be dereferenced without first casting it to the correct pointer type. */
    int x = 50;
    void *ptr1 = &x;
    cout << *(int *)ptr1 << endl;

    int a = 10;
    float b = 12.5;
    char c = 'A';

    void *ptr2;

    ptr2 = &a;
    cout << *(int *)ptr2 << endl;

    ptr2 = &b;
    cout << *(float *)ptr2 << endl;

    ptr2 = &c;
    cout << *(char *)ptr2 << endl;
    return 0;
}
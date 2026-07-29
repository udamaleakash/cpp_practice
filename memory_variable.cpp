#include <iostream>

int a = 10;                 // Data Segment
int g;                      // BSS

const int c = 100;          // Read-Only Data (typically)
static int s = 50;          // Data Segment
static int us;              // BSS

int main()
{
    int b = 20;             // Stack

    static int x = 30;      // Data Segment
    static int y;           // BSS

    const int z = 40;       // Stack (typically)

    char ch = 'A';          // Stack

    char str[] = "Hello";   // Stack
    const char *ptr = "World"; // ptr -> Stack, "World" -> Read-Only Data

    int *arr = new int[5];  // arr -> Stack, allocated array -> Heap
    //same for in c  int *arr = (int *)malloc(5 * sizeof(int));

    delete[] arr;
    // free(arr);

    return 0;
}
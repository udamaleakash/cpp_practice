#include <iostream>

extern "C"
{
    // simple add function
    int add(int a, int b)
    {
        return a + b;
    }

    // simple multiply function
    int multiply(int a, int b)
    {
        return a * b;
    }

    // simple subtract function
    int subtract(int a, int b)
    {
        return a - b;
    }
}
#include <iostream>
#define DEBUG // defines DEBUG before compilation.

using namespace std;
#define MAX 200

int main()
{
#ifdef DEBUG // checks whether DEBUG is defined.
    cout << "Debug mode\n";
#endif
    // Since DEBUG is defined, the code inside #ifdef is compiled.

#if MAX == 100
    cout << "Max defined\n";
#elif MAX == 200
    cout << "Max not defined\n";
#else
    cout << "Max not defined\n";
#endif
    return 0;
}
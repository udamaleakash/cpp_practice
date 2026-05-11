/* Morden C++ */
/* Phase 1: Memory Management */
/* RULE OF 3/5 */

#include <iostream>
#include <cstring>
using namespace std;
class Loan
{
private:
    char *ptr; // wild pointer

public:
    Loan()
    {
        cout << "Constructor called" << endl;
        ptr = new char[256];      // allocate memory for the pointer
        strcpy(ptr, "Home loan"); // initialize the pointer with some value
    }
    ~Loan()
    {
        delete[] ptr; // dangling pointer
        cout << "Destructor called" << endl;
    }
    // Copy constructor
    Loan(const Loan &l) // deep copy
    {
        cout << "Copy constructor called" << endl;
        ptr = new char[256]; // allocate new memory for the copy
        strcpy(ptr, l.ptr);  // copy the content of the original pointer to the new pointer
    }
    // Copy assignment operator
    Loan &operator=(const Loan &l) // deep copy
    {
        cout << "Copy assignment operator called" << endl;
        if (this)
        {
            delete[] ptr;        // delete the existing memory
            ptr = new char[256]; // allocate new memory for the copy
            strcpy(ptr, l.ptr);  // copy the content of the original pointer to the new pointer
        }
        return *this;
    }
    // Move constructor
    Loan(Loan &&l) noexcept // move semantics
    {
        cout << "Move constructor called" << endl;
        ptr = l.ptr;     // transfer ownership of the pointer
        l.ptr = nullptr; // set the original pointer to null to avoid double deletion
    }
    // Move assignment operator
    Loan &operator=(Loan &&l) noexcept // move semantics
    {
        cout << "Move assignment operator called" << endl;
        if (this)
        {
            delete[] ptr;    // delete the existing memory
            ptr = l.ptr;     // transfer ownership of the pointer
            l.ptr = nullptr; // set the original pointer to null to avoid double deletion
        }
        return *this;
    }
};

int main()
{
    Loan l1;
    Loan l2 = l1; // copy constructor called
    Loan l3;
    l3 = l1;            // copy assignment operator called
    Loan l4 = move(l1); // move constructor called
    Loan l5;
    l5 = move(l2); // move assignment operator called
    return 0;
}

// ********* RAII *******
/* RAII is a C++ programming technique where resource management is tied to object lifetime using constructors and destructors.

Resource like memory, file, or lock is acquired in an object’s constructor and released in its destructor. Because the destructor runs automatically when the object goes out of scope

e.g Problem without RAII here,
void func()
{
    int *ptr = new int(10);

    // some error happens
    return;

    delete ptr; // never executed -> memory leak
} 
Here memory leaks because delete is skipped.

RAII solves this automatically.
RAII solves this problem by ensuring that resources are released automatically when the object goes out of scope, even if an error occurs or the function returns early.

Benefits of RAII?
-> Prevents resource leaks
-> Exception safe
-> Automatic cleanup
-> Cleaner code
-> Scope-based management
-> Less manual delete/close.

How RAII Works
When object is created:
Constructor runs
Resource acquired

When object goes out of scope:
Destructor runs automatically
Resource released automatically

This works even if:
exception occurs
function returns early
error happens

*/

// ********* Stack vs Heap ******** 
/* Stack Memory

Stack memory is:
Automatically managed
Fast
Used for local variables and function calls

Example:

#include <iostream>
using namespace std;

int main()
{
    int x = 10;

    cout << x << endl;

    return 0;
}

Here x is stored in stack memory.
When function ends:
memory automatically removed

// Heap Memory 

Heap memory is:

Dynamically allocated
Manually managed
Larger than stack
Slightly slower

Example:

#include <iostream>
using namespace std;

int main()
{
    int *ptr = new int(100);

    cout << *ptr << endl;

    delete ptr;

    return 0;
}

Here:

ptr variable → stack
actual integer (100) → heap

 */
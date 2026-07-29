
// ** 1) static variable:-
/* A static variable is created only once, stored for the entire lifetime of the program, and retains its value between function calls.

Memory allocated only once.
Lifetime is the entire program.
Value is not reset on each function call.
Typically stored in the Data or BSS segment.
 */

 // ** 2) Static Member Function (C++):-
 /* A static member function belongs to the class instead of an object, so it can be called using the class name without creating an object.

Easy points to remember
Belongs to the class, not an object.
Can be called as ClassName::function().
Can access only static data members directly.
Has no this pointer. 
stored in Text (Code) Segment*/


/*
3). Static Data Member (Static Variable)
Definition

A static data member belongs to the class, not to individual objects.

Only one copy exists in memory, shared by all objects.
Memory is allocated once (Data Segment).
It must be defined outside the class (before C++17, unless using inline).

Why do we use it?
->To store data that is common to all objects.
To count the number of objects created.
To store configuration/settings shared by every object.

if we decared static int x =100; globally without class, then
x is accessible only within this .cpp file.
if another file can do extern int x;   // Error
because static gives it internal linkage.

*/

/*
Static Member Function
Definition

A static member function belongs to the class, not to any object.

It can be called without creating an object.
It can access only static data members.
It cannot access non-static members because there is no this pointer.

Why do we use it?
To operate on static members.
For utility/helper functions related to the class.
To provide class-level functionality without needing an object.
*/

/*
Static local variable	❌ No	static int count; inside a function
Static global variable	❌ No	static int x = 10;
Static data member	    ✅ Yes	static int count; inside a class
Static member function	✅ Yes	static void show(); inside a class
 */

/* Static data member or variable	static int count;
stored in --> Data Segment (or BSS if uninitialized)	->(Lifetime)Entire program

Static member function	static void show();	Text (Code) Segment	Entire program
*/

// ----------------------------------------------------------------------------
#include <iostream>
using namespace std;

class Counter
{
public:
    static int count;
    static void increment()
    {
        count++;
    }
    static void display()
    {
        cout << "Count = " << count << endl;
    }
};

int Counter::count = 0;
int main()
{
    Counter::increment(); // call function without class object
    Counter::increment();
    Counter::increment();
    Counter::increment();

    Counter::display();

    return 0;
}
// output->  Count = 4
#include <iostream>
#include <memory>
using namespace std;

/* Smart pointers automatically manage dynamically allocated memory. They prevent memory leaks, automatically release resources when objects go out of scope, and make exception-safe code easier to write. 

Smart Pointer	Ownership	Copy Allowed	Auto Delete
unique_ptr	Single owner	❌ No	✅ Yes
shared_ptr	Multiple owners	✅ Yes	✅ Yes
weak_ptr	No ownership	✅ Yes	❌ Doesn't own



*/

int main()
{
    int *ptr = new int(50);
    cout << *ptr << endl;
    delete ptr;

    unique_ptr<int> p1(new int(100)); // ownership cannot be shared.
    cout << *p1 << endl;

    shared_ptr<int> p2(new int(90));
    shared_ptr<int> p3 = p2;
    cout << *p2 << " " << *p3 << endl;

    return 0;
}
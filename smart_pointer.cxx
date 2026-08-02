/*
 unique_ptr:-

A smart pointer that provides exclusive ownership of an object. It cannot be copied but can transfer ownership using std::move().

shared_ptr:-

A smart pointer that allows multiple owners of the same object using reference counting. The object is automatically destroyed when the last owner is gone.

weak_ptr:-

A smart pointer that observes an object managed by a shared_ptr without owning it. It does not increase the reference count and is mainly used to avoid circular references.


/* Smart pointers automatically manage dynamically allocated memory. They prevent memory leaks, automatically release resources when objects go out of scope, and make exception-safe code easier to write.

Smart Pointer	Ownership	Copy Allowed	Auto Delete
unique_ptr	Single owner	❌ No	✅ Yes
shared_ptr	Multiple owners	✅ Yes	✅ Yes
weak_ptr	No ownership	✅ Yes	❌ Doesn't own
*/

#include <iostream>
#include <memory>
using namespace std;

class Test
{
public:
    Test()
    {
        cout << "Constructor Called" << endl;
    }

    ~Test()
    {
        cout << "Destructor Called" << endl;
    }

    void show()
    {
        cout << "Show Function" << endl;
    }
};
// below is shared classes e.g
class A
{
public:
    void show()
    {
        cout << "A class call here\n";
    }
};

class B
{
    shared_ptr<A> ptr_a;

public:
    B(shared_ptr<A> e)
    {
        ptr_a = e;
    }
    void display()
    {
        ptr_a->show();
    }
};

int main()
{
    cout << "===== unique_ptr =====" << endl;
    unique_ptr<Test> up = make_unique<Test>();
    up->show();

    // unique_ptr<Test> up2 = up;      // ❌ Not Allowed

    unique_ptr<Test> up2 = move(up); // Transfer ownership

    if (up == nullptr)
        cout << "up is NULL after move" << endl;

    up2->show();

    cout << "\n===== shared_ptr =====" << endl;

    shared_ptr<Test> sp1 = make_shared<Test>();

    cout << "Count = " << sp1.use_count() << endl;

    shared_ptr<Test> sp2 = sp1;

    cout << "Count = " << sp1.use_count() << endl;

    cout << "\n===== weak_ptr =====" << endl;

    weak_ptr<Test> wp = sp1;

    cout << "Count = " << sp1.use_count() << endl; // Still 2

    if (auto temp = wp.lock())
    {
        temp->show();
    }

    // shared class e.g.
    cout << "shared class e.g->\n";
    shared_ptr<A> a = make_shared<A>();
    cout << a.use_count() << endl; // 1

    B b1(a);
    b1.display();
    cout << a.use_count() << endl; // 2

    cout << "\nEnd of main()" << endl;

    return 0;
}
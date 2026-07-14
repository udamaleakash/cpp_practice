#include <iostream>
#include <string.h>
using namespace std;
// Here we study about friend function and friend class

// First Friend function can access private and protected members of class
class A
{
    int a = 10;
    friend void show(A &obj); // friend function declaration
};

void show(A &obj)
{
    cout << "Value of a: " << obj.a << endl;
}

// Now see, Friend class can access private and protected members of class
class B; // forward declaration
class C
{
    int c = 30;
    friend class B; // friend class declaration
};

class B
{
public:
    void display(C &obj)
    {
        obj.c = 40; // B can access private member of C
        cout << "Value of c: " << obj.c << endl;
    }
};

int main()
{
    A obj;
    show(obj);

    C obj1;
    B obj2;
    obj2.display(obj1);

    return 0;
}
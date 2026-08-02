#include <iostream>
#include <string.h>
using namespace std;

// Here we study about friend function and friend class
// First Friend function can access private and protected members of class
class A
{
private:
    int x = 10;

    friend void show();
};

void show()
{
    A obj;                 // Create object
    cout << obj.x << endl; // Access private member
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
    show();

    C obj1;
    B obj2;
    obj2.display(obj1);

    return 0;
}

// output:
// Value of a: 10
// Value of c: 40

#include <iostream>
using namespace std;

/*
 Singlton class means only one object of that class can be created.
 1. Constructor of that class should be private.
 2. Static method should be created which will return the object of that class.
 Cant create object of that class using new keyword.
 */

class Akash
{
    Akash() // 1.
    {
        cout << "constructor called" << endl;
    }

public:
    static Akash &get_obj() // 2.
    {
        static Akash obj;
        return obj;
    }
    void display()
    {
        cout << "Akash class obj created\n";
    }
};
int main()
{
    Akash &a1 = Akash::get_obj();
    Akash &a2 = Akash::get_obj();
    a1.display();
    a2.display();
    cout << &a1 << endl;
    cout << &a2 << endl;
    if (&a1 == &a2)
    {
        cout << "Both are same object\n";
    }
    else
    {
        cout << "Both are different object\n";
    }

    return 0;
}

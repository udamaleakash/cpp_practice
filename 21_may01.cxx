
#include <stdio.h>
#include <iostream>
using namespace std;

class Base
{
public:
    virtual void show()
    {
        cout << "Base";
    }
};
class Derived : public Base
{
public:
    void show()
    {
        cout << "Derived";
    }
};

int main()
{
    // Base *ptr = new Derived();
    // ptr->show();

    int x = 10;
    int *const p = &x;
    cout << *p;

    // char *p = new char [100];
    // delete[] p;


    return 0;
}
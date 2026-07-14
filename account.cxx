#include <iostream>
using namespace std;

// virtual keyword
/* virtual is useful only when all three conditions are met:

There is inheritance ✅
The derived class overrides the function ✅
The function is called through a base class pointer or reference ✅
If any one of these is missing, virtual has no visible effect.

virtual works with base pointer refernce and
checks actual object runtime





Virtual Function-
Base class says: "I already have an implementation. You may override it if you want."

Pure Virtual Function- virtual void display() = 0;
Base class says: "I don't have an implementation for this behavior. You must implement it in the derived class."

Q. When do you use a virtual function and when do you use a pure virtual function?
answer:
Virtual function: I use it when I need runtime polymorphism. The base class provides a default implementation, and derived classes can override it if needed. It is typically used with inheritance and base class pointers or references.

Pure virtual function: I use it when I want to create an abstract class and force every derived class to provide its own implementation. This is useful when the base class defines only a common interface and cannot provide meaningful behavior itself.


*/

class A
{
public:
    virtual void display()
    {
        cout << "Display from A" << endl;
    }
};

class B : public A
{
public:
    void display() override
    {
        cout << "Display from B" << endl;
    }
};

int main()
{
    A *obj = new B(); // base pointer refernce
    obj->display();
}

/*
The virtual keyword is required to achieve runtime polymorphism. It only has an effect when a derived class overrides a base class function and the function is invoked through a base class pointer or reference. If we call the function directly using a derived object, the compiler already knows the object's type, so virtual makes no difference. */
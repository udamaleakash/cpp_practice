// mutlithreding

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class Animal
{
public:
    virtual void sound() // Virtual Function
    {
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal
{
public:
    void sound() override
    {
        cout << "Dog barks" << endl;
    }
};

class Cat : public Animal
{
public:
    void sound() override
    {
        cout << "Cat meows" << endl;
    }
};

int main()
{
    Animal *ptr1 = new Animal();
    ptr1->sound();

    Animal *ptr2 = new Dog();
    ptr2->sound();

    // Animal *ptr3 = dynamic_cast<Dog >;

    return 0;
}
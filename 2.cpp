#include <iostream>
using namespace std;
// virtual finction & vtable e.g.
class Animal
{
public:
    virtual void speak()
    {
        cout << "Animal speaks";
    }
};

class Dog : public Animal
{
public:
    void speak() override
    {
        cout << "Dog barks";
    }
};
int main()
{

    Animal *a = new Dog();
    a->speak(); // calls Dog's speak (runtime decision)

    // Animal *b = new Animal();
    // b->speak();

    // Dog *d1;
    // d1->speak();

    // Animal *s1 = new Dog();
    // s1->speak();
    return 0;
}
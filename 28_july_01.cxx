/*
Polymorphism
│
├── Compile Time (Static Binding)
│   ├── Function Overloading
│   ├── Operator Overloading
│   └── Templates
│
└── Runtime (Dynamic Binding)
    └── Function Overriding (using virtual functions)


Operator Overloading = Same operator, new meaning for your class.
Example: Define what + does for Point objects.
Function Overriding = Same function name, new implementation in a derived class.
Example: Animal::sound() → Dog::sound().
*/

// 1 operator overloading

#include <iostream>
using namespace std;
class A
{

public:
    int x = 0;
    A(int a)
    {
        x = a;
    }
    A operator+(A obj)
    {
        return A(x + obj.x);
    }
};

// 2. Function Overriding
class AA
{
public:
    virtual void show()
    {
        cout << "AA class, show called" << endl;
    }
};

class BB : public AA
{
public:
    void show() override
    /* override doesn't change the program's behavior. It asks the compiler to verify that the derived function really overrides a virtual function in the base class, helping catch mistakes like wrong names, parameter lists, or const qualifiers at compile time. */
    {
        cout << "BB class, show called" << endl;
    }
};

// ------ Funtion overloading------
int max(int a, int b)
{
    return (a > b ? a : b);
}
double max(double a, double b)
{
    return (a > b ? a : b);
}
char max(char a, char b)
{
    return (a > b ? a : b);
}

// ------- Compile time : using Template ----------

template <typename T>
T max_tem(T a, T b)
{
    return (a > b ? a : b);
}

template <typename T>
T square(T value)
{
    return (value * value);
}

// ----------- Class Template -------------
template <typename T>
class TemA
{
public:
    T value;
    TemA(T a)
    {
        value = a;
    }
    void show()
    {
        cout << value << endl;
    }
};

int main()
{
    // --------Compile time operator overloading------
    A a1(90);
    A a2(50);
    A a3 = a1 + a2;
    cout << a3.x << endl;

    // --------Runtime Fun overriding-------------

    AA *aa1 = new BB();
    aa1->show();

    // -------compile time Funtion overloading--------
    cout << max(10, 20) << endl;
    cout << max(10.4, 20.5) << endl;
    cout << max('a', 'b') << endl;
    // writing the same logic multiple times.so overcome we use template below i.e. generic

    // ------- compile time : using Template ----------

    cout << "compile time : using Template" << endl;
    cout << max_tem(10, 20) << endl;
    cout << max_tem(10.4, 20.5) << endl;
    cout << max_tem('a', 'b') << endl;

    // ------ class template --------
    TemA<int> t1(23); // compiler decides the type when you write. (if you write TemA t1(23) is ok but not good behaviour)
    TemA<double> t2(23.56);
    TemA<char> t3('H');
    TemA<string> t4("Hello");
    t1.show();
    t2.show();
    t3.show();
    t4.show();

    return 0;
}

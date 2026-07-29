#include <iostream>
using namespace std;

// Abstraction = Hide complexity
class Car
{
public:
    void start()
    {
        engine();
    }

private:
    void engine()
    {
        cout << "Engine started\n";
    }
};

// Encapsulation = Protect data
class Bank
{
private:
    int balance = 0;

public:
    void deposit(int amount)
    {
        balance += amount;
    }
    void show()
    {
        cout << balance << endl;
    }
};

// Inheritance
class A
{
public:
    void showA()
    {
        cout << "class show A\n";
    }
};
class B : public A
{
public:
    void showB()
    {
        cout << "class show B\n";
    }
};

// Polymorphism
class sum
{
public:
    void add(int a, int b)
    {
        cout << a + b << endl;
    }
    void add(double a, double b)
    {
        cout << a + b << endl;
    }
};

// operator overloading
class Number
{

public:
    int value = 0;

    Number(int n)
    {
        value = n;
    }
    Number operator+(Number obj)
    {
        return (value + obj.value);
    }
};

int main()
{
    // Abstraction:- Showing only necessary information while hiding implementation details.
    Car c;
    c.start();

    // Encapsulation:- Wrapping data and functions together inside a class while restricting direct access using access specifiers.
    Bank b;
    b.deposit(2000);
    b.show();

    // Inheritance:- It Allows one class to reuse properties and methods of another class.
    B b1;
    b1.showA();
    b1.showB();

    // Polymorphism:- One interface Multiple forms.
    /* Compile Time Polymorphism  */
    // Function Overloading
    sum s1;
    s1.add(500, 200);
    s1.add(500.45, 200.23);
    // oprator overloading
    Number n1(100);
    Number n2(100);
    Number n3 = n1 + n2;
    cout<<n3.value;
    // for better understanding of operator overloading / polymorphism see 28_july_01.cxx file
}
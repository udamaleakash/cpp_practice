// // OOP Concepts
// /* --------------------- */

// /* The 4 Pillars of OOP (C++)
// 1. Encapsulation → “Protect data”

// Bundle data + methods, restrict access.

// 2. Abstraction → “Hide complexity”

// Show only essential features.

// 3. Inheritance → “Reuse code”

// One class acquires properties of another.

// 4. Polymorphism → “One interface, many forms”

// Same function behaves differently. */

// /* --------------------- */

// // 1. Encapsulation (Data Hiding)
// // 👉 Definition

// // Encapsulation means binding data (variables) and methods (functions) together in a single unit (class) and restricting direct access to some of the object's data.

// // 👉 In short:
// // “Hide data + control access using getters/setters.”

// // ✅ Real-life Example

// // Think of a bank account:

// // You cannot directly change your balance
// // You must use methods like deposit() or withdraw()
// // 💻 C++ Example

// #include <iostream>
// using namespace std;

// class BankAccount
// {
// private:
//     double balance; // hidden data

// public:
//     // setter
//     void deposit(double amount)
//     {
//         balance += amount;
//     }

//     // getter
//     double getBalance()
//     {
//         return balance;
//     }
// };

// int main()
// {
//     BankAccount acc;

//     acc.deposit(1000);
//     cout << "Balance: " << acc.getBalance();

//     return 0;
// }

// // 2. Abstraction (Hiding Complexity)
// // 👉 Definition

// // Abstraction means showing only essential details and hiding internal implementation.

// // 👉 In short:
// // “What to do” is visible, “how it works” is hidden.
// // ✅ Real-life Example

// // Think of a car 🚗

// // You just press accelerator
// // You don’t know how engine works internally
// // 💻 C++ Example
// #include <iostream>
// using namespace std;

// class Car
// {
// public:
//     void start()
//     {
//         cout << "Car started" << endl;
//         igniteEngine(); // hidden logic
//     }

// private:
//     void igniteEngine()
//     {
//         cout << "Engine ignition process..." << endl;
//     }
// };

// int main()
// {
//     Car c;
//     c.start(); // user only sees start()

//     return 0;
// }
// // 🔑 Key Points
// // Hides internal logic
// // User interacts with simple interface
// // Achieved using:
// // Classes
// // Abstract classes (pure virtual functions)

// // Interview Tip (Important)

// // 👉 One-liner difference:

// // Encapsulation = How you protect data
// // Abstraction = How you hide complexity

/* ------------*/

// #include <iostream>
// using namespace std;
// class base
// {
// public:
//     void show()
//     {
//         cout << "base class show function" << endl;
//     }
// };
// class derived1 : public base
// {
// public:
//     void show1()
//     {
//         cout << "derived class show1 function" << endl;
//     }
// };
// class derived2 : public derived1
// {
// public:
//     void show2()
//     {
//         cout << "derived class show2 function" << endl;
//     }
// };

// int main()
// {
//     // base *b;
//     // b->show();
//     // derived1 *d;
//     // d->show();
//     // d->show1();
//     // derived2 d2;
//     // d2.show();

//     base *b1 = new derived2();
//     b1->show();
//     return 0;
// }

/* #include <iostream>
using namespace std;

class Base {
public:
    ~Base() {
        cout << "Base destructor" << endl;
    }
    void show(){

    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    Base* b = new Derived();
    delete b;
} */

/* #include <iostream>
using namespace std;
int main()
{
    return 0;
} */

#include <iostream>
using namespace std;
class base
{
private:
    int data = 0;
    double data2 = 0.00;

public:
    base()
    {
        
    }
    void add(int a, int b)
    {
        data = a + b;
        cout << data << endl;
    }
    void add(double a, double b)
    {
        data2 = a * b;
        cout << data2 << endl;
    }
    ~base() {}
};

int main()
{
    base b;
    b.add(5, 10);
    b.add(10.5, 2.5);
}